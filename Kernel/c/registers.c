#include <registers.h>

#define REGISTERS 18

uint64_t registerBackup[REGISTERS];
char backupDone;

void makeBackup(uint64_t* regs){
    for(int i = 0; i < REGISTERS; i++){
        registerBackup[i] = regs[i];
    }

    backupDone = 1;
    return;
}

char isBackupDone(){ 
    return backupDone == 1; 
}

uint64_t* getRegs() {
    if (isBackupDone())
        return registerBackup;
    return NULL;
}


//TEMP
/*
void printRegs(){
    char* regName[] = {
        "RAX: ", "RBX: ", "RCX: ", "RDX: ", "RSI: ", "RDI: ", 
        "RBP: ", "R8: ", "R9: ", "R10: ", "R11: ", "R12: ",
        "R13: ", "R14: ", "R15: ", "RSP: ", "RIP: ", "RFLAGS: "  
    };
    vdNewline();
    vdPrint("Register Status: ");
    if(backupDone == 0)
        vdPrint("Nao mano.");
    else{
        uint64_t reg;
        for(int i = 0; i < REGISTERS; i++){
            reg = registerBackup[i];
            vdPrint(regName[i]);
            vdPrintDec(reg);
            vdNewline();
        }
    }
}
*/
