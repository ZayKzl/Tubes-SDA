# Nama executable Anda
TARGET = tubes-sda

# Compiler yang digunakan
CC = gcc

# Direktori source
SRCDIR = src
CJSON_SRCDIR = cJSON

# Direktori include
INCDIR = include
CJSON_INCDIR = cJSON

# Semua file .c di direktori src
SRCS = $(wildcard $(SRCDIR)/*.c)
# Semua file .c di direktori cJSON
CJSON_SRCS = $(wildcard $(CJSON_SRCDIR)/*.c)

# Semua file .o yang akan dibuat dari file .c di src
OBJS = $(patsubst $(SRCDIR)/%.c, obj/%.o, $(SRCS))
# Semua file .o yang akan dibuat dari file .c di cJSON
CJSON_OBJS = $(patsubst $(CJSON_SRCDIR)/%.c, obj/cJSON_%.o, $(CJSON_SRCS))

# Flags compiler
CFLAGS = -Wall -g
# Flags include path
IFLAGS = -I$(INCDIR) -I$(CJSON_INCDIR)

# Flags linker
LDFLAGS =

# Direktori untuk file objek
OBJDIR = obj

.PHONY: all clean run

all: $(OBJDIR) $(TARGET)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(TARGET): $(OBJS) $(CJSON_OBJS)
	$(CC) $(OBJS) $(CJSON_OBJS) -o $@ $(LDFLAGS)

# Rule untuk mengkompilasi file .c di src
obj/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

# Rule untuk mengkompilasi file .c di cJSON
obj/cJSON_%.o: $(CJSON_SRCDIR)/%.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJDIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)