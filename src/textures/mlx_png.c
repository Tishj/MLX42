/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_png.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 15:31:31 by tbruinem      #+#    #+#                 */
/*   Updated: 2022/02/17 15:45:11 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"
#include "lodepng.h"

t_mlx_texture*  mlx_load_png(const char* path)
{
    t_mlx_texture*  png = calloc(1, sizeof(t_mlx_texture));
    if (!png) {
        exit(1);
    }
    png->bytes_per_pixel = 4;
    if (!lodepng_decode32_file(&png->pixels, (unsigned int*)&png->width, (unsigned int*)&png->height, path)) {
        exit(1);
    }
    return png;
}

bool    mlx_draw_png(t_mlx_image* image, t_mlx_texture* texture, unsigned int x, unsigned int y)
{
	int32_t	i;
	int32_t	j;
	uint8_t	*pixel;

	if (!texture || !image)
		return (mlx_log(MLX_WARNING, MLX_NULL_ARG));
	if (texture->width > image->width || \
		texture->height > image->height)
		return (mlx_log(MLX_ERROR, "XPM is larger than image!"));
	i = -1;
	while (++i < texture->height)
	{
		j = -1;
		while (++j < texture->width)
		{
			pixel = &texture->pixels[(i * texture->width + j) * \
			texture->bytes_per_pixel];
			mlx_putpixel(image, x + j, y + i, *pixel << 24 | \
			*(pixel + 1) << 16 | *(pixel + 2) << 8 | *(pixel + 3));
		}
	}
	return (true);
}

void    mlx_delete_png(t_mlx_texture* png)
{
    free(png->pixels);
}

t_mlx_image*    mlx_png_to_image(t_mlx* mlx, const char* path)
{
	t_mlx_texture*  png;
	t_mlx_image*    img;

	if (!mlx || !path)
		return ((void *)mlx_log(MLX_WARNING, MLX_NULL_ARG));
	png = mlx_load_png(path);
	if (!png)
		return (NULL);
	img = mlx_new_image(mlx, png->width, png->height);
	if (!img)
		return (NULL);
	if (!mlx_draw_png(img, png, 0, 0))
		return (NULL);
	mlx_delete_png(png);
	return (img);
}
