/*
  LNGpng.cpp
*/

#include <GL/LNG/LNGpng.h>

using namespace std;

LNGpng::LNGpng() : size(LNGsize(0, 0)), depth(0), col_type(0),
  interlace_type(0), compress_type(0), filter_type(0),
  png_depth(0), p_depth(0), b_depth(0), pals(0), num_pals(0), alpha(0),
  image(0), palette(0)
{
}

LNGpng::~LNGpng()
{
  Finalize();
}

void LNGpng::Finalize(void)
{
  if(palette){ delete[] palette; palette = 0; }
  if(image){ delete[] image; image = 0; }
}

void LNGpng::C4hFunc(png_structp png_ptr, png_row_infop ri, png_bytep data)
{
#define C4HFUNC_PIX(c) ((((c) << 2) & 0x30) | ((c) & 0x03))
  png_uint_32 rowb = (ri->width + 1) / 2;
  png_byte *p = data + rowb / 2;
  png_byte *q = data + rowb;
  if(rowb % 2) *(--q) = C4HFUNC_PIX(*p >> 4);
  while(p-- > data){
    *(--q) = C4HFUNC_PIX(*p & 0x0f);
    *(--q) = C4HFUNC_PIX(*p >> 4);
  }
  ri->bit_depth = 4;
  ri->pixel_depth = 4;
  ri->rowbytes = rowb;
}

void LNGpng::ReadFunc(png_structp png_ptr, png_bytep data, png_size_t length)
{
  fread(data, length, 1, (FILE *)png_get_io_ptr(png_ptr));
}

bool LNGpng::LoadRaw(string &filepath)
{
  Finalize();
  bool result = true;
  FILE *fp = fopen(filepath.c_str(), "rb");
  if(!fp) return false;
  png_struct *png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
  if(!png_ptr){
    fclose(fp);
    return false;
  }
  png_info *info_ptr = png_create_info_struct(png_ptr);
  if(!info_ptr){
    png_destroy_read_struct(&png_ptr, 0, 0);
    fclose(fp);
    return false;
  }
  png_info *end_info = png_create_info_struct(png_ptr);
  if(!end_info){
    png_destroy_read_struct(&png_ptr, &info_ptr, 0);
    fclose(fp);
    return false;
  }
  png_set_read_fn(png_ptr, fp, ReadFunc);
  png_read_info(png_ptr, info_ptr);
  png_get_IHDR(png_ptr, info_ptr,
    &size.w, &size.h, (int *)&depth, (int *)&col_type,
    (int *)&interlace_type, (int *)&compress_type, (int *)&filter_type);
  png_depth = depth; p_depth = depth == 16 ? 8 : depth; b_depth = 0; pals = 0;
  alpha = col_type & 4;
  if(col_type == PNG_COLOR_TYPE_RGB || col_type == PNG_COLOR_TYPE_RGB_ALPHA)
    b_depth = png_depth = 24;
  else pals = 1 << (b_depth = png_depth == 2 ? 4 : p_depth);
  if(col_type & PNG_COLOR_MASK_ALPHA) png_set_strip_alpha(png_ptr);
  if(png_depth == 2) png_set_read_user_transform_fn(png_ptr, C4hFunc);
  else if(png_depth == 16) png_set_strip_16(png_ptr);
  if(col_type== PNG_COLOR_TYPE_RGB || col_type == PNG_COLOR_TYPE_RGB_ALPHA)
    png_set_bgr(png_ptr);
  png_read_update_info(png_ptr, info_ptr);
  if(pals > 0){
    if(!(palette = new png_color[pals])) result = false;
    else{
      if(col_type == PNG_COLOR_TYPE_PALETTE){
        png_color *pal;
        png_get_PLTE(png_ptr, info_ptr, &pal, (int *)&num_pals);
        if(num_pals > pals) num_pals = pals;
        memset(palette, 0, sizeof(png_color) * pals);
        memcpy(palette, pal, sizeof(png_color) * num_pals);
        // png_destroy_??(&pal) ?
      }else{
        png_build_grayscale_palette(p_depth, palette);
      }
    }
  }
  int row_bytes = (size.w * b_depth + 31) / 32 * 4;
  if(!result || !(image = new GLubyte[row_bytes * size.h])) result = false;
  else{
    GLubyte **rows = new GLubyte *[size.h];
    if(!rows) result = false;
    else{ // reverse top and bottom
      for(int y = 0; y < size.h; y++)
        rows[y] = image + (size.h - 1 - y) * row_bytes;
      png_read_image(png_ptr, rows);
      delete[] rows;
      png_read_end(png_ptr, end_info);
    }
  }
  png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
  fclose(fp);
  return result;
}
