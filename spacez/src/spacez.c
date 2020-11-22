#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Ku {
	unsigned char *data;
	int size;
} ku;

struct Registers {
	int a;
	int b;
	int c;
	int d;
	int ip;
} regs;

int *program;
int psize;

int countlines(FILE* fp){
	int lines = 0;
	while (!feof(fp)){
		char ch = fgetc(fp);
		if (ch == '\n'){
			lines++;
		}
	}
	return lines;
}

void queue_init(){
	ku.size = 0;
}

void regs_init(){
	regs.a = 0;
	regs.b = 0;
	regs.c = 0;
	regs.d = 0;
	regs.ip = 0;
}

void queue_insert(unsigned char element){
	if (ku.size == 0){
		ku.data = malloc(1);
		ku.data[0] = element;
		ku.size++;
	}
	else {
		ku.size++;
		ku.data = realloc(ku.data, ku.size);
		for (int i = ku.size-1; i > 0; i--)
			ku.data[i] = ku.data[i-1];
		ku.data[0] = element;
	}
}

unsigned char queue_get(){
	unsigned char element = ku.data[ku.size-1];
	ku.size--;
	ku.data = realloc(ku.data, ku.size);
	return element;
}

void queue_clear(){
	ku.size = 0;
	free(ku.data);
}

int get_spaces_number(char* line){
	int len = strlen(line);
    int snum = 0;
    for (int i = 0; i < len; i++){
        if (line[i] == '\n')
            break;
        if (line[i] != ' ')
            return -1;
        snum++;
    }
	return snum;
}

int get_register(int regnum){
	switch (regnum){
        case 0:
            return regs.a;
            break;
        case 1:
            return regs.b;
            break;
        case 2:
            return regs.c;
        	break;
		case 3:
			return regs.d;
			break;
	}
}

void set_register(int regnum, int value){
    switch (regnum){
        case 0: 
            regs.a = value;
            break;
        case 1: 
            regs.b = value;
            break;
        case 2: 
            regs.c = value;
            break;
		case 3:
			regs.d = value;
			break;
    }
}


/*void logger(){
	puts("\n--------");
	printf("queue:\n");
	printf("\t ->  ");
	for (int i = 0; i < ku.size; i++){
		printf("%02x ", ku.data[i]);
	}
	printf(" ->\n");
	puts("regs:");
	printf("\ta: %08x\n", regs.a);
	printf("\tb: %08x\n", regs.b);
	printf("\tc: %08x\n", regs.c);
	printf("\td: %08x\n", regs.d);
	printf("\tip: %08x\n", regs.ip);
	puts("--------\n");
}*/

void start_program(){
	bool running = true;
	bool error = false;
	//puts("start");
	while (true){
		//logger();
		//puts("next instruction");
		switch (program[regs.ip]){
			case 0: {
				//puts("clear queue");
				queue_clear();
				regs.ip++;
				break;
			}
			case 1: {
				//puts("push reg1");
				regs.ip++;
				int tmp;
				if (program[regs.ip] < 0 || program[regs.ip] > 3)
					error = true;
				else
					tmp = get_register(program[regs.ip]);
				if (!error){
					for (int i = 0; i < 4; i++){
						queue_insert(tmp & 0xff);
						tmp >>= 8;
					}
				}
				regs.ip++;
				break;
			}
			case 2: {
                //puts("push1 reg1");
                regs.ip++;
                int tmp;
                if (program[regs.ip] < 0 || program[regs.ip] > 3)
                    error = true;
                else
                    tmp = get_register(program[regs.ip]);
                if (!error){ 
                    queue_insert(tmp & 0xff);
                }
                regs.ip++;
                break;
            }
			case 3: {
                //puts("push2 reg1");
                regs.ip++;
                int tmp;
                if (program[regs.ip] < 0 || program[regs.ip] > 3)
                    error = true;
                else
                    tmp = get_register(program[regs.ip]);
                if (!error){ 
                    for (int i = 0; i < 2; i++){
                        queue_insert(tmp & 0xff);
                        tmp >>= 8;
                    }
                }
                regs.ip++;
                break;
            }
			case 4: {
                //puts("pop reg1");
				regs.ip++;
				int tmp = 0;
				for (int i = 0; i < 4; i++){
					tmp |= (queue_get() << (i*8));
				}
				if (program[regs.ip] < 0 || program[regs.ip] > 3)
                    error = true;
                else
                    set_register(program[regs.ip], tmp);
				regs.ip++;
                break;
            }
			case 5: {
                //puts("pop1 reg1");
                regs.ip++;
                int tmp = 0;
                tmp |= queue_get();
                if (program[regs.ip] < 0 || program[regs.ip] > 3)
                    error = true;
                else
                    set_register(program[regs.ip], tmp);
                regs.ip++;
                break;
            }
			case 6: {
                //puts("pop2 reg1");
                regs.ip++;
                int tmp = 0;
                for (int i = 0; i < 2; i++){
                    tmp |= (queue_get() << (i*8));
                }
                if (program[regs.ip] < 0 || program[regs.ip] > 3)
                    error = true;
                else
                    set_register(program[regs.ip], tmp);
                regs.ip++;
                break;
            }
			case 7: {
                //puts("reg1 = value");
				regs.ip++;
				int value = program[regs.ip];
				regs.ip++;
				if (program[regs.ip] < 0 || program[regs.ip] > 3)
                    error = true;
                else{
                    set_register(program[regs.ip], value);
				}
				regs.ip++;
                break;
            }
			case 8: {
                //puts("reg1 = reg2");
				regs.ip++;
                int value;
				if (program[regs.ip] < 0 || program[regs.ip] > 3)
                    error = true;
                else
                    value = get_register(program[regs.ip]);
                regs.ip++;
				if (!error){
                	if (program[regs.ip] < 0 || program[regs.ip] > 3)
                    	error = true;
               		else
                    	set_register(program[regs.ip], value);
                }
				regs.ip++;
                break;
            }
			case 9: {
                //puts("reg1 += reg2");
				regs.ip++;
                int value;
                if (program[regs.ip] < 0 || program[regs.ip] > 3)
                    error = true;
                else
                    value = get_register(program[regs.ip]);
                regs.ip++;
                if (!error){
                    if (program[regs.ip] < 0 || program[regs.ip] > 3)
                        error = true;
                    else
                        set_register(program[regs.ip], (int)(get_register(program[regs.ip]) + value));
                }
                regs.ip++;
                break;
            }
			case 10: {
                //puts("reg1 -= reg2");
				regs.ip++;
                int value;
                if (program[regs.ip] < 0 || program[regs.ip] > 3)
                    error = true;
                else
                    value = get_register(program[regs.ip]);
                regs.ip++;
                if (!error){
                    if (program[regs.ip] < 0 || program[regs.ip] > 3)
                        error = true;
                    else
                        set_register(program[regs.ip], (int)(get_register(program[regs.ip]) - value));
                }
                regs.ip++;
                break;
            }
			case 11: {
                //puts("reg1 *= reg2");
				regs.ip++;
                int value;
                if (program[regs.ip] < 0 || program[regs.ip] > 3)
                    error = true;
                else
                    value = get_register(program[regs.ip]);
                regs.ip++;
                if (!error){
                    if (program[regs.ip] < 0 || program[regs.ip] > 3)
                        error = true;
                    else
                        set_register(program[regs.ip], (int)(get_register(program[regs.ip]) * value));
                }
                regs.ip++;
                break;
            }
			case 12: {
                //puts("reg1 /= reg2");
				regs.ip++;
                int value;
                if (program[regs.ip] < 0 || program[regs.ip] > 3)
                    error = true;
                else
                    value = get_register(program[regs.ip]);
                regs.ip++;
                if (!error){
                    if (program[regs.ip] < 0 || program[regs.ip] > 3)
                        error = true;
                    else
                        set_register(program[regs.ip], (int)(get_register(program[regs.ip]) / value));
                }
                regs.ip++;
                break;
            }
			case 13: {
                //puts("reg1 %= reg2");
				regs.ip++;
                int value;
                if (program[regs.ip] < 0 || program[regs.ip] > 3)
                    error = true;
                else
                    value = get_register(program[regs.ip]);
                regs.ip++;
                if (!error){
                    if (program[regs.ip] < 0 || program[regs.ip] > 3)
                        error = true;
                    else
                        set_register(program[regs.ip], (int)(get_register(program[regs.ip]) % value));
                }
                regs.ip++;
                break;
            }
			case 14: {
                //puts("reg1 &= reg2");
				regs.ip++;
                int value;
                if (program[regs.ip] < 0 || program[regs.ip] > 3)
                    error = true;
                else
                    value = get_register(program[regs.ip]);
                regs.ip++;
                if (!error){
                    if (program[regs.ip] < 0 || program[regs.ip] > 3)
                        error = true;
                    else
                        set_register(program[regs.ip], (int)(get_register(program[regs.ip]) & value));
                }
                regs.ip++;
                break;
            }
			case 15: {
                //puts("reg1 |= reg2");
				regs.ip++;
                int value;
                if (program[regs.ip] < 0 || program[regs.ip] > 3)
                    error = true;
                else
                    value = get_register(program[regs.ip]);
                regs.ip++;
                if (!error){
                    if (program[regs.ip] < 0 || program[regs.ip] > 3)
                        error = true;
                    else
                        set_register(program[regs.ip], (int)(get_register(program[regs.ip]) | value));
                }
                regs.ip++;
                break;
            }
			case 16: {
                //puts("reg1 ^= reg2");
				regs.ip++;
                int value;
                if (program[regs.ip] < 0 || program[regs.ip] > 3)
                    error = true;
                else
                    value = get_register(program[regs.ip]);
                regs.ip++;
                if (!error){
                    if (program[regs.ip] < 0 || program[regs.ip] > 3)
                        error = true;
                    else
                        set_register(program[regs.ip], (int)(get_register(program[regs.ip]) ^ value));
                }
                regs.ip++;
                break;
            }
			case 17: {
                //puts("jump");
				regs.ip++;
				regs.ip = program[regs.ip];
				if (regs.ip >= psize)
					error = true;
                break;
            }
			case 18: {
                //puts("jump if reg1 reg2");
				regs.ip++;
				int operation = program[regs.ip];
				regs.ip++;
				int reg1, reg2;
				if (program[regs.ip] < 0 || program[regs.ip] > 3)
                    error = true;
                else
                    reg1 = get_register(program[regs.ip]);
                regs.ip++;
				
				if (error){
					break;
				}
                
				if (program[regs.ip] < 0 || program[regs.ip] > 3)
                    error = true;
                else
                    reg2 = get_register(program[regs.ip]);
				
				if (error){
					break;
				}

				regs.ip++;
                int value = program[regs.ip];
                if (value >= psize)
                    error = true;

				if (error){	
					break;
				}

				switch (operation){
					case 0: {
						if (reg1 == reg2)
							regs.ip = value;
						else
							regs.ip++;
						break;
					}
					case 1: {
						if (reg1 != reg2) regs.ip = value;
						else regs.ip++;
						break;
					}
					case 2: {
						if (reg1 > reg2) regs.ip = value;
                        else regs.ip++;
						break;
					}
					case 3: {
						if (reg1 < reg2) regs.ip = value;
                        else regs.ip++;
						break;
					}
					default:
						error = true;
						break;
				}
                break;
            }
			case 19: {
				//puts("input");
				regs.ip++;
				int len = program[regs.ip];
				char *temp;
				temp = malloc(len);
				scanf("%s", temp);
				for (int i = 0; i <= strlen(temp); i++){
					queue_insert(temp[i]);
				}
				regs.ip++;
				break;
			}
			case 20: {
				//puts("print");
				char ch;
				while ((ch = queue_get()) != 0){
					putchar(ch);
				}
				regs.ip++;
				break;
			}
			case 21: {
				//puts("stop");
				running = false;
				break;
			}
			default: {
				puts("strange instruction. error");
				error = true;
				break;
			}
		}
		if (!running)
			break;
		if (error){
			puts("Error!");
			break;
		}
	}
}

int main(int argc, char* argv[]){
	ssize_t read;
	size_t len = 0;
	FILE *program_text;
	char* line = NULL;
	if (argc != 2){
		puts("Usage:\n./spacez <source code>");
		exit(1);
	}
	program_text = fopen(argv[1], "r");
	if (program_text == NULL){
		puts("Error opening file!");
		exit(1);
	}

	// load program
	int lines = countlines(program_text);
	rewind(program_text);
	program = malloc(lines * sizeof(int));
	psize = lines;

	int i = 0;
	while ((read = getline(&line, &len, program_text)) != -1) {
		int code = get_spaces_number(line);
		if (code == -1){
			puts("Wrong syntax!");
			fclose(program_text);
			exit(1);
		} else {
			program[i] = code;
		}
		i++;
	}
	
	queue_init();
	regs_init();
	start_program();

	fclose(program_text);
	return 0;
}
