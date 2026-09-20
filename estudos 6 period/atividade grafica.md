# Questões de analise
- A ordem das transformações importa porque aplicar a rotação antes ou depois da translação altera a posição e a orientação final do objeto.
- A ordem importa pois, cada transformação é aplicada em sequencia, e portanto aplicada sobre o resultado da anterior
- Usamos `glPushMatrix()` e `glPopMatrix()` para **salvar e restaurar a matriz de transformação**, permitindo aplicar transformações a um objeto sem afetar os outros objetos da cena.
- O sistema de coordenadas é importante na visualização 3D porque **define a posição, a orientação e o movimento dos objetos no espaço, permitindo que a cena seja representada corretamente pela câmera**.
- A projeção em perspectiva faz com que **objetos mais distantes pareçam menores e os mais próximos maiores**, criando uma percepção de profundidade e tornando a cena 3D mais realista.

# (1°
Toro original tem sem nhuma transformação
![[Pasted image 20260918103918.png]]
# (2°
plotando os eixos x,y,z
![[Pasted image 20260918103937.png]]
# (3°
## rotações

glRotatef(90.0, 1.0, 0.0, 0.0);
![[Pasted image 20260918104230.png]]
glRotatef(90.0, 0.0, 1.0, 0.0);
![[Pasted image 20260918105300.png]]
glRotatef(90.0, 0.0, 0.0, 1.0);
![[Pasted image 20260918105352.png]]
# (5°
## Transladando

lTranslatef(30.0, 0.0, 0.0);
![[Pasted image 20260918105815.png]]
glTranslatef(0.0, 10.0, -2/0.0);
![[Pasted image 20260918105911.png]]

# (4°
## Escalonado

glScalef(1.5, 1.5, 1.5);
![[Pasted image 20260918110056.png]]
glScalef(0.5, 0.5, 0.5); 
![[Pasted image 20260918110122.png]]
glScalef(1.0, 2.0, 0.5); 
![[Pasted image 20260918110349.png]]

