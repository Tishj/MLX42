/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_exit.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 02:43:22 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/02/14 11:50:17 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

void	mlx_delete_xpm42(t_xpm **xpm)
{
	if (!*xpm)
	{
		mlx_log(MLX_WARNING, MLX_NULL_ARG);
		return ;
	}
	mlx_freen(2, (*xpm)->texture.pixels, *xpm);
	*xpm = NULL;
}

static void	mlx_free_imagedata(void	*content)
{
	t_mlx_image		*img;

	img = content;
	mlx_freen(3, img->context, img->pixels, img->instances);
}

void	mlx_quit(t_mlx *mlx)
{
	if (!mlx)
	{
		mlx_log(MLX_WARNING, MLX_NULL_ARG);
		return ;
	}
	glfwSetWindowShouldClose(mlx->window, true);
}

/**
 * All of glfw & glads resources are cleaned up by the terminate function.
 * Now its time to cleanup our own mess.
 */
void	mlx_terminate(t_mlx *mlx)
{
	t_mlx_ctx	*mlxctx;

	if (!mlx)
	{
		mlx_log(MLX_WARNING, MLX_NULL_ARG);
		return ;
	}
	if (!glfwWindowShouldClose(mlx->window))
		glfwSetWindowShouldClose(mlx->window, true);
	mlxctx = mlx->context;
	glfwTerminate();
	mlx_lstclear((t_mlx_list **)(&mlxctx->hooks), &free);
	mlx_lstclear((t_mlx_list **)(&mlxctx->render_queue), &free);
	mlx_lstclear((t_mlx_list **)(&mlxctx->images), &mlx_free_imagedata);
	mlx_freen(2, mlxctx, mlx);
}
