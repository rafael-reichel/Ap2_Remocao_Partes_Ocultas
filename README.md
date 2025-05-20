# Ap2_Remocao_Partes_Ocultas
Demonstração de Técnicas de Renderização 3D
📌 Visão Geral
Este projeto demonstra três técnicas fundamentais de renderização 3D através da visualização de quatro cubos coloridos. As técnicas implementadas são:

Back-Face Culling (Eliminação de faces ocultas)

Painter's Algorithm (Algoritmo do pintor)

Z-Buffer (Buffer de profundidade)

🛠️ Tecnologias Utilizadas
OpenGL

GLUT (OpenGL Utility Toolkit)

Linguagem C++

🎮 Controles
Tecla	Ação
1	Ativa Back-Face Culling
2	Ativa Painter's Algorithm
3	Ativa Z-Buffer
Setas	Rotaciona a cena (esquerda/direita)
H	Mostra/oculta ajuda
ESC	Sai do programa
🎨 Técnicas Implementadas
Back-Face Culling
Remove faces não visíveis do observador

Melhora desempenho eliminando cálculos desnecessários

Visualização: 4 cubos posicionados estrategicamente

Painter's Algorithm
Renderiza objetos do mais distante para o mais próximo

Requer ordenação manual dos objetos

Visualização: 4 planos coloridos em diferentes profundidades

Z-Buffer
Técnica padrão em GPUs modernas

Armazena informação de profundidade para cada pixel

Visualização: 4 cubos em posições e profundidades variadas

📊 Observações
O código inclui um sistema de ajuda visual (tecla H)

Cada cubo possui cor distinta para facilitar a identificação

A rotação da cena ajuda a visualizar os efeitos de cada técnica
