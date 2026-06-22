NAME        = gnl.a

# 📄 Archivos fuentes y cabeceras
SRCS        = get_next_line.c get_next_line_utils.c
OBJS        = $(SRCS:.c=.o)
HEADER      = get_next_line.h

BONUS_SRCS  = get_next_line_bonus.c get_next_line_utils_bonus.c
BONUS_OBJS  = $(BONUS_SRCS:.c=.o)
BONUS_HDR   = get_next_line_bonus.h

# ⚙️ Configuración del compilador (Modifica el BUFFER_SIZE si lo necesitas)
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -D BUFFER_SIZE=1024

# 🎨 Colores y formato
GREEN       = \033[0;32m
CYAN        = \033[0;36m
RESET       = \033[0m
BOLD        = \033[1m

all: $(NAME)

# 🔄 Compilación básica
$(NAME): Makefile $(HEADER) $(OBJS)
	@ar -rcs $(NAME) $(OBJS)
	@printf "📖 $(GREEN)[▰▰▰▰▰▰▰▰▰▰] 100%%$(RESET) Get_Next_Line listo.\n"

# ➕ Compilación de los Bonus
bonus: Makefile $(BONUS_HDR) $(BONUS_OBJS)
	@ar -rcs $(NAME) $(BONUS_OBJS)
	@printf "🎖️  $(GREEN)[▰▰▰▰▰▰▰▰▰▰] 100%%$(RESET) Get_Next_Line Bonus listo.\n"

# 🛠️ Regla implícita para compilar los .c a .o
%.o: %.c $(HEADER) $(BONUS_HDR) Makefile
	@printf "⚙️  $(GREEN)Compilando GNL:$(RESET) $<\r"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS) $(BONUS_OBJS)
	@echo "🧹 $(CYAN)Objetos de GNL eliminados.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "🗑️  $(CYAN)Archivo gnl.a eliminado.$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus
