#!/usr/bin/python
# -*- coding:utf-8 -*-

import subprocess
import os
import sys

def is_tool(prog):
    for dir in os.environ['PATH'].split(os.pathsep):
        if os.path.exists(os.path.join(dir, prog)):
            try:
                subprocess.call([os.path.join(dir, prog)],
                                stdout=subprocess.PIPE,
                                stderr=subprocess.STDOUT)
            except OSError, e:
                return False
            return True
    return False
    
def help():
	print "\n----------------------------------\nGravando um programa:"	
	print "Após conectar o MSP430 na porta USB, entre com o comando \n\"mspdbug rf2500\"\nEm algumas instalações é necessário ter acesso administrativo\n"
	print "\"prog <PROGRAMA>.elf\" irá gravar o arquivo no chip. \"run\" irá começar a executar o programa no chip enquanto \"exit\" irá fechar o debugador"
	print "O programa pode ser interrompido a qualquer momento com \"Ctrl+C\". \"run\" irá resumir a execução"
	
	print "\n\nÉ possível gravar um chip tanto com os arquivos *.hex quanto com os *.elf"
	print "Caso queira utilizar a biblioteca para algum outro MSP, compile os código com:"
	print "\"make DEVICE=msp430g2553\"\t <- para gerar o binário para o MSP430G2553\n"
    
def main():
	if is_tool('msp430-gcc') == False:
		print "MSPGCC não instalado!"
		resposta=raw_input("Começar processo de instalação? (y/n): ")
		if(resposta=='y'):
			print "Pacotes que serão instalados: gcc-msp430 binutils-msp430 msp430-libc msp430mcu mspdebug"
			os.system("sudo apt-get install gcc-msp430 binutils-msp430 msp430-libc msp430mcu mspdebug -s")
			if is_tool('msp430-gcc') != False:
				print "Pacotes instalados com sucesso!"
			else:
				print "\nFalha na instalação dos pacotes. Por favor verifique seus repositórios e sua conexão com a internet!"
				return
	else:
		print "MSPGCC Instalado!"
		resposta=raw_input("Deseja instruções de como proceder para gravar o chip?(y/n): ")
		if(resposta=='y'):
			help()
		
if __name__ == "__main__":
	try:
		if (sys.argv[1] == "-h") or (sys.argv[1] == "--help"):
			help()
	except:
	    main()
