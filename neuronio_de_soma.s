# Criado pelo Lucas Pereira. Data da Finalização: 07-12-2020

.data
	ta:.float 0.02 # Taxa de Atualização
	peso1:.float 0.00 # Peso 1
	peso2: .float 0.80 # Peso 2
	erro:.float 0.00 # Erro
	nuloFloat: .float 0.00
	epoca: .word 1 # Epoca
	
	mensagem: .ascii "Digite um numero\n"
	
.text
	la $s1, epoca # guarda o endereço de memória da variável "epoca" no registrador $s1
	la $t0, peso1 # guarda o endereço de memória da variável "peso1" no registrador $t0
	la $t1, peso2 # guarda o endereço de memória da variável "peso2" no registrador $t1
	la $t2, erro  # guarda o endereço de memória da variável "erro" no registrador $t2
	la $t3, ta    # guarda o endereço de memória da variável "ta" no registrador $t3
	la $t4, nuloFloat    # guarda o endereço de memória da variável "ta" no registrador $t3
	
	lw $s1, 0($s1)   # atribue o valor de epoca no registrador $s1
	lwc1 $f0, 0($t0) # atribue o valor de peso1 no registrador $f0
	lwc1 $f1, 0($t1) # atribue o valor de peso2 no registrador $f1
	lwc1 $f2, 0($t2) # atribue o valor de erro no registrador $f2
	lwc1 $f3, 0($t3) # atribue o valor de ta no registrador $f3
	lwc1 $f9, 0($t4) # atribue o valor de ta no registrador $f3
	
	main:
		# O neurônio vai ser treinado com os dados do registrador $a0 e $a0 que é incrementado até o número 7
		addi $t5, $t5, 1 # Vai atribuir o valor 1 ao registrador $t5
	
		while: 
		 slti $t6, $t5, 8 # Se $t5 for menor a 8, atribuir $t6 o valor 1 senão valor 0
		 beq $t6, $0, sair # Se $t6 for igual a zero, pular para "sair"
		# Enquanto $t5 for menor a 8, faça:
		  add $a0, $0, $t5
		  add $a1, $0, $t5
		  jal treine_neuronio

		  addi $t5, $t5, 1 # Adicione 1 ao registrador $t5
		  j while # Volte para o início do loop

		sair:
		  # Mostra a mensagem
		  li $v0, 4
		  la $a0, mensagem
		  syscall

		  # Ler o dado do usuário e atribue ao registrador $t0
		  li $v0, 5
		  syscall
		  add $t0, $0, $v0

		  # Mostra a mensagem de novo
		  li $v0, 4
		  la $a0, mensagem
		  syscall

		  # Ler o dado do usuário e atribue ao registrador $aa
		  li $v0, 5
		  syscall
		  add $a1, $0, $v0 

		  add $a0, $0, $t0 # atribue o valor de $t0 a variavel $a0


		  jal perceptron # chama o neurônio treinado para calcular os numeros

		  # Mostra o resultado do neurônio na tela
		  add.s $f12, $f20, $f8
		  li $v0, 2
		  syscall
	
	
	# Manda o OS finalizar o programa
	li $v0, 10
	syscall
	
	###############################################################
	# Procedimentos de cálculos

	treine:

	perceptron:
		mtc1 $a0, $f4       # Move o argumento $a0 (entrada) para o registrador $f6
		cvt.s.w $f4, $f4    # Converte o valor inteiro para double %f6 = (double) int %f6
		mul.s $f5, $f0, $f4

		mtc1 $a1, $f6       # Move o argumento $a0 (entrada) para o registrador $f6
		cvt.s.w $f6, $f6    # Converte o valor inteiro para double %f6 = (double) int %f6
		mul.s $f7, $f1, $f6

		mul.s $f8, $f8, $f9 
		add.s $f8, $f5, $f7

		#mfc1 $v0, $f8
		jr $ra

	calcule_erro:
		add $t0, $a0, $a1
		mtc1 $t0, $f4
		cvt.s.w $f4, $f4
		sub.s $f2, $f4, $f8 # Atualize o erro ($f2)

		jr $ra # retornar o comando para a rotina principal

	atualize_peso1:
		addi $sp, $sp, -4
		sw $ra, 0($sp) # Guarda o endereço da função chamadora

		jal faca_calculos_de_peso

		lw $ra, 0($sp) # Retorna o endereço da função chamadora
		addi $sp, $sp, 4

		add.s $f0, $f0, $f7 # Soma com o peso atual
		jr $ra  # retornar o comando para a rotina principal

	atualize_peso2:
		addi $sp, $sp, -4
		sw $ra, 0($sp) # Guarda o endereço da função chamadora

		jal faca_calculos_de_peso

		lw $ra, 0($sp) # Retorna o endereço da função chamadora
		addi $sp, $sp, 4

		add.s $f1, $f1, $f7 # Soma com o peso atual
		jr $ra   # retornar o comando para a rotina principal

	faca_calculos_de_peso:
		mul.s $f5, $f2, $f3 # Registrador $f5 = erro * ta
		mtc1 $a0, $f6       # Move o argumento $a0 (entrada) para o registrador $f6
		cvt.s.w $f6, $f6    # Converte o valor inteiro para double %f6 = (double) int %f6
		mul.s $f7, $f5, $f6 # Multiplica $f7 = $f5 (erro * ta) * entrada

		jr $ra

	treine_neuronio:
		addi $sp, $sp, -4
		sw $ra, 0($sp) # Guarda o endereço da função chamadora

		jal perceptron # Chama o neurônio
		jal calcule_erro # Calcula o erro
		jal atualize_peso1 # Atualiza o peso 1
		jal atualize_peso2 # Atualiza o peso 2

		lw $ra, 0($sp) # Retorna o endereço da função chamadora
		addi $sp, $sp, 4

		jr $ra   # retornar o comando para a rotina principal
