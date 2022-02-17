# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile_Linux.mk                                  :+:    :+:             #
#                                                      +:+                     #
#    By: W2Wizard <w2.wizzard@gmail.com>              +#+                      #
#                                                    +#+                       #
#    Created: 2021/12/28 01:01:14 by W2Wizard      #+#    #+#                  #
#    Updated: 2022/02/17 15:30:22 by tbruinem      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME 	=	libmlx42.a
ARCHIVE	=	-ldl -lglfw -lGL -lX11 -lpthread -lXrandr -lXi
HEADERS =	-I include lib/lodepng
