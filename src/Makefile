CC       = gcc
CFLAGS   = -Wall
LDFLAGS  =
OBJFILES = client_utils.o main.o file_utils.o general_utils.o matrix_utils.o queue.o server_utils.o
TARGET   = stacktest

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~
