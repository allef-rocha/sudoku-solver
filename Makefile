CC			= gcc
CFLAGS		= -Wall -Werror -Ofast -std=c99 -Iinclude -g

LINKER		= gcc
LFLAGS		= -Wall -Werror -Ofast -std=c99 -g

SRCDIR		= src
OBJDIR		= obj
BINDIR		= bin

SOURCES		:= $(wildcard $(SRCDIR)/*.c)
INCLUDES	:= $(wildcard $(SRCDIR)/*.h)
OBJECTS		:= $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
RM			= rm -rf

TARGET		= sudoku

ifeq (run,$(firstword $(MAKECMDGOALS)))
 RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
 $(eval $(RUN_ARGS):;@:)
endif

.PHONY: all
all: $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
	@$(RM) $(OBJDIR)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(RM) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"

.PHONY: run
run: $(BINDIR)/$(TARGET)
	@./$(BINDIR)/$(TARGET) $(filter-out $@, $(MAKECMDGOALS))

.PHONY: $(MAKECMDGOALS)