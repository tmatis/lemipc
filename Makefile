NAME := lemipc
CC := gcc
CFLAGS := -Wall -Wextra -Werror
LIBFTDIR := libft
LIBFT := $(LIBFTDIR)/libft.a
LIBMLXDIR := minilibx
LIBMLX	= minilibx/libmlx.a
LIBFTINC := $(LIBFTDIR)/includes
LIBMLXINC := $(LIBMLXDIR)
LIBS := -L $(LIBFTDIR) -lft -L $(LIBMLXDIR) -lmlx -lXext -lX11 -lm 


ifneq ($(filter debug redebug,$(MAKECMDGOALS)),)
	CFLAGS += -g
endif

SRCSDIR := srcs
OBJSDIR_RELEASE := .build/release
OBJSDIR_DEBUG := .build/debug
INCDIR := includes

INCLUDES := -I $(INCDIR) -I $(LIBFTINC) -I $(LIBMLXINC)

SRCS_MAIN := main.c

# board srcs

SRCS += board/board_create.c \
		board/board_get.c \
		board/board_lock.c \
		board/board_open.c \
		board/board_disconnect.c \
		board/board_compute_size.c

# pawn srcs

SRCS += pawn/pawn_get.c \
		pawn/pawn_join_board.c \
		pawn/pawn_count_team_player.c \
		pawn/pawn_leave_board.c \
		pawn/pawn_is_dead.c \
		pawn/pawn_move.c

# graphic_visualizer srcs

SRCS += graphic_visualizer/graphic_visualizer_launch.c \
		graphic_visualizer/render_board.c \
		graphic_visualizer/get_team_color.c

# render utils srcs

SRCS += graphic_visualizer/render_utils/frame_draw_line.c \
		graphic_visualizer/render_utils/frame_draw_rectangle.c \
		graphic_visualizer/render_utils/frame_put_pixel.c \
		graphic_visualizer/render_utils/put_string.c \
		graphic_visualizer/render_utils/frame_init.c

# msgbox srcs

SRCS += msgbox/msgbox_receive.c \
		msgbox/msgbox_send.c

# Strategy srcs

SRCS += strategy/strategy_choose_team_target.c \
		strategy/get_distance.c \
		strategy/strategy_choose_next_move.c

# game srcs

SRCS += game/game_routine.c \
		game/game_start.c

# utils srcs

SRCS += utils/int_map.c \
		utils/is_in_board_bound.c

OBJS_MAIN_RELEASE := $(addprefix $(OBJSDIR_RELEASE)/,$(SRCS_MAIN:.c=.o))
OBJS_MAIN_DEBUG := $(addprefix $(OBJSDIR_DEBUG)/,$(SRCS_MAIN:.c=.o))
OBJS_RELEASE := $(addprefix $(OBJSDIR_RELEASE)/,$(SRCS:.c=.o))
OBJS_DEBUG := $(addprefix $(OBJSDIR_DEBUG)/,$(SRCS:.c=.o))

ALL_SRCS := $(SRCS) $(SRCS_MAIN)

DEPS_RELEASE := $(addprefix $(OBJSDIR_RELEASE)/,$(ALL_SRCS:.c=.d))
DEPS_DEBUG := $(addprefix $(OBJSDIR_DEBUG)/,$(ALL_SRCS:.c=.d))

DFLAGS	= -MMD -MF $(@:.o=.d)

NAME_DEBUG := $(NAME)_debug

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(LIBMLX):
	$(MAKE) -C $(LIBMLXDIR)

$(NAME): $(LIBFT) $(LIBMLX) $(OBJS_RELEASE) $(OBJS_MAIN_RELEASE)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS_RELEASE) $(OBJS_MAIN_RELEASE) $(LIBS)

$(NAME_DEBUG): $(LIBFT) $(LIBMLX) $(OBJS_DEBUG) $(OBJS_MAIN_DEBUG)
	$(CC) $(CFLAGS) -o $(NAME_DEBUG) $(OBJS_DEBUG) $(OBJS_MAIN_DEBUG) $(LIBS)

debug: $(NAME_DEBUG)

unit: $(LIBFT) $(LIBMLX) $(OBJS_DEBUG)
	libft/scripts/car.sh $(OBJS_DEBUG) $(LIBS)

-include $(DEPS_RELEASE)
$(OBJSDIR_RELEASE)/%.o: $(SRCSDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) $(DFLAGS) -c $< -o $@

-include $(DEPS_DEBUG)
$(OBJSDIR_DEBUG)/%.o: $(SRCSDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) $(DFLAGS) -c $< -o $@

clean:
	make -C $(LIBFTDIR) clean
	make -C $(LIBMLXDIR) clean
	rm -rf .build

fclean: clean
	make -C $(LIBFTDIR) fclean
	rm -f $(NAME) $(NAME_DEBUG)

re: fclean all

redebug: fclean debug

.PHONY: all clean fclean re debug redebug