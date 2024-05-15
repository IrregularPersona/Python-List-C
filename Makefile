PROJECTNAME = tempName
OUTPUT_DIR = build
LIB_DIR = -L ./lib/
INCLUDE_DIR = -Iinclude/
SRC = main.c
default: 
	gcc $(SRC) -o $(OUTPUT_DIR)/$(PROJECTNAME) $(INCLUDE_DIRS) $(LIB_DIRS) $(LIBS)
