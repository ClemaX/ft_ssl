NAME = ft_ssl
DIST = debug

# Compiler
CC = clang
LD = clang

# Paths
SRCDIR = srcs
INCDIR = includes

OBJDIR = objs/$(DIST)
BINDIR = bin/$(DIST)
RUNDIR = run/$(DIST)
LIBDIR = libs

# Libraries to include
LIBS = libft
LIBA = $(LIBS:%=$(LIBDIR)/%.a)
LDLIBS = $(LIBA:$(LIBDIR)/lib%.a=-l%)

# Flags
CFLAGS = -Wall -Wextra -Werror -DOCB_DIST=$(DIST) -I$(INCDIR) $(LIBS:%=-I$(LIBDIR)/%/includes)
DFLAGS = -MT $@ -MMD -MP -MF $(OBJDIR)/$*.d
LFLAGS = -L$(LIBDIR)

ifeq ($(DIST), debug)
	CFLAGS += -g3 -fsanitize=address -fsanitize=undefined# -fsanitize=leak
	LFLAGS += -g3 -fsanitize=address -fsanitize=undefined# -fsanitize=leak
endif

SRCS = $(addprefix $(SRCDIR)/,\
	main.c\
	ssl_cmd.c\
)

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
DEPS = $(OBJS:.o=.d)

COMPILE.c = $(CC) $(DFLAGS) $(CFLAGS) -c
COMPILE.o = $(LD) $(LFLAGS)

RUN = $(BINDIR)/$(NAME) md5 -s "foo"

all: $(BINDIR)/$(NAME)

# Libraries
$(LIBA): $(LIBDIR)/%.a: $(LIBDIR)/%/
	make -C $< NAME=../$(notdir $@)

# Directories
$(OBJDIR) $(BINDIR):
	@echo "MK $@"
	mkdir -p $@

# Objects
$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.c $(OBJDIR)/%.d | $(OBJDIR)
	@mkdir -p '$(@D)'
	@echo "CC $<"
	$(COMPILE.c) $< -o $@

# Dependencies
$(DEPS): $(OBJDIR)/%.d:
include $(wildcard $(DEPS))

# Binaries
$(BINDIR)/$(NAME): $(OBJS) | $(BINDIR) $(LIBA)
	@echo "LD $@"
	$(COMPILE.o) $^ -o $@ $(LDLIBS)

clean:
	@echo "RM $(OBJDIR)"
	rm -rf $(OBJDIR)

fclean: clean
	@echo "RM $(LIBA)"
	rm -rf $(LIBA)
	@echo "RM $(BINDIR)"
	rm -rf $(BINDIR)
	@echo "RM $(RUNDIR)"
	rm -rf $(RUNDIR)

re: fclean all

run: $(BINDIR)/$(NAME)
	@echo "RUN $(RUN)"
	@echo
	$(RUN)

.PHONY: clean fclean re run

$(VERBOSE).SILENT:
