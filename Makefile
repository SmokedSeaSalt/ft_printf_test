LIBPATH := ../ft_printf
LIBRARY := $(LIBPATH)/libft.a

OUTDIR = outs/
# Compiler and flags
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address -lbsd -I $(LIBPATH)/

SRCS = test_ft_printf.cc

# Create a list of output .out files based on test.c files
OUTS = $(patsubst %.c, $(OUTDIR)test_%.out, $(ALLSRCS))

# Default target: build all tests
all: $(LIBRARY) $(OUTDIR) $(OUTS)

$(LIBRARY):
	make -C $(LIBPATH)

$(OUTDIR):
	mkdir -p $(OUTDIR)

# Rule to create .out files from .c files
$(OUTDIR)%.out: %.c $(LIBRARY)
	$(CC) $(CFLAGS) -o $@ $< $(LIBRARY)

# Run all .out files
run:
	@for file in $(OUTDIR)*.out; do \
		echo "Running $$file"; \
		./$$file; \
	done

# Clean up the output files
clean:
	rm -rf $(OUTDIR)
	make clean -C $(LIBPATH)

fclean: clean
	make fclean -C $(LIBPATH)

cleantest:
	rm -rf $(OUTDIR)

re: fclean
	$(MAKE) $(LIBPATH)
	$(MAKE) all
