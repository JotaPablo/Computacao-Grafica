#include <GL/glut.h> //O arquivo glut.h inclui, além dos protótipos das funções GLUT, os arquivos gl.h e glu.h,
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define PI 3.14159265358979323846

void desenhaNuvens();
void circulo(float x, float y, float raio);
void desenhaNuvens();
void desenhaCalcada();
void display(void);

void desenhaPredio(){

  glBegin(GL_QUADS);
  //Base
    glColor3ub(142, 91, 70); // Laranja da base do prédio
    glVertex2f(0.0, 25.0);   // Ponto inferior esquerdo
    glVertex2f(30.0, 25.0);  // Ponto inferior direito
    glVertex2f(30.0, 40.0); // Ponto superior direito
    glVertex2f(0.0, 40.0);  // Ponto superior esquerdo
  //Trapézio em cima
    glColor3ub(24, 6, 10); //Marrom do trapézio do telhado
    glVertex2f(0.0, 40.0);   // Ponto inferior esquerdo
    glVertex2f(30.0, 40.0);  // Ponto inferior direito
    glVertex2f(26.0, 45.0);   // Ponto superior direito
    glVertex2f(4.0, 45.0);  // Ponto superior esquerdo

  //Listra em baixo do telhado (borda)
    glColor3ub(35, 42, 76);   // Um azul
    glVertex2f(0.0, 38.0);   // Ponto inferior esquerdo
    glVertex2f(30.0, 38.0);  // Ponto inferior direito
    glVertex2f(30.0, 40.0);   // Ponto superior direito
    glVertex2f(0.0, 40.0);  // Ponto superior esquerdo
      //Linha superior
      glColor3ub(255, 255, 255);
      glVertex2f(0.0, 40.0);   // Ponto inferior esquerdo
      glVertex2f(30.0, 40.0);  // Ponto inferior direito
      glVertex2f(30.0, 39.8);   // Ponto superior direito
      glVertex2f(0.0, 39.8);  // Ponto superior esquerdo

  glEnd();
  

}


int main(int argc, char** argv){
  glutInit(&argc, argv); //Estabelece contato com sistema de janelas
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); //Cores dos pixels serão expressos em RGB
  glutInitWindowSize (1000, 600); //Posição inicial do canto superior esquerdo da janela a ser criada
  glutInitWindowPosition (00, 00); //Estabelece o tamanho (em pixels) da janela a ser criada
  glutCreateWindow (argv[1]); //Cria uma nova janela com valor de retorno (não usado)
  // que a identifica, caso tenha mais de uma
  glClearColor(1.0, 1.0, 1.0, 0.0); //selecionar cor de fundo (Branco)
  glOrtho(0.0, 100.0, 0.0, 60.0, -1.0, 1.0); //define as coordenadas do volume de recorte (clipping volume),
  glutDisplayFunc(display); //Função callback chamada para fazer o desenho
  glutMainLoop(); //Depois de registradas as callbacks, o controle é entregue ao sistema de janelas
  return 0;
}

void display(void){
  glClear(GL_COLOR_BUFFER_BIT); ////Limpa a janela de visualização com a cor de fundo especificada

  //glBegin(GL_POINTS);
  //glBegin(GL_LINES);
  //glBegin(GL_LINE_STRIP);
  //glBegin(GL_LINE_LOOP);
  //glBegin(GL_QUADS);
  //glBegin(GL_QUAD_STRIP);
  //glBegin(GL_TRIANGLES);
  //glBegin(GL_TRIANGLE_STRIP);
  //glBegin(GL_TRIANGLE_FAN);
  
  //Cor do Ceú
  glBegin(GL_QUADS);
    //Uma cor mais clara de azul em baixo
    glColor3ub(87, 134, 214);
    glVertex2f(0,0);
    glVertex2f(100, 0);
    //Coloca uma nova cor mais escura para o topo
    glColor3ub(16, 59, 162);
    glVertex2f(100,60);
    glVertex2f(0,60);
  glEnd();

  //Desenha o sol
  glColor3ub(255, 255, 102); // Cor amarelo claro
    circulo(98.0, 57.0, 6.0); // Círculo externo

  glColor3ub(255, 204, 0); // Cor amarela
    circulo(98.0, 57.0, 5.5); // Círculo central
  //Desenho as nuvens
  //desenhaNuvens();
    
  //Desenha chão
  glColor3ub(27, 47, 15); // Define a cor do chão
    glBegin(GL_QUADS);
        glVertex2f(0.0, 0.0);   // Ponto inferior esquerdo
        glVertex2f(100.0, 0.0);  // Ponto inferior direito
        glVertex2f(100.0, 30.0); // Ponto superior direito
        glVertex2f(0.0, 30.0);  // Ponto superior esquerdo
    glEnd();

  //Desenha calçada
  desenhaCalcada();
 

  //Desenha prédios a esquerda
  desenhaPredio();
  
    


  //Desenha arvores

  //Desenha gramas


  //Desenha flores


  //Desenha bancos

  



 

  glFlush(); 
}

void desenhaCalcada(){
  glColor3ub(100, 100, 100); // Cinza para a estrada
    glBegin(GL_QUADS);
    //Base
      glVertex2f(0.0, 0.0); // Inferior esquerdo
      glVertex2f(100.0, 0.0); // Inferior direito
      glVertex2f(100.0, 10.0); // Superior direito
      glVertex2f(0.0, 10.0); //Superior esquerdo
    //Parte Central
        glVertex2f(30.0, 0.0);   // Ponto inferior esquerdo
        glVertex2f(70.0, 0.0);   // Ponto inferior direito
        glVertex2f(55.0, 30.0);  // Ponto superior direito
        glVertex2f(45.0, 30.0);  // Ponto superior esquerdo
    glEnd();

}







// Desenhar as nuvens
void desenhaNuvens() {

    glColor3ub(255, 255, 255); // Coloca a cor para branco
  
    // Nuvem 1 (10 círculos)
    circulo(15.0, 42.0, 1.5); // Círculo 1
    circulo(16.5, 43.0, 1.4); // Círculo 2
    circulo(14.0, 43.5, 1.3); // Círculo 3
    circulo(16.0, 41.5, 1.2); // Círculo 4
    circulo(17.0, 42.0, 1.4); // Círculo 5
    circulo(14.5, 41.0, 1.1); // Círculo 6
    circulo(15.5, 44.0, 1.3); // Círculo 7
    circulo(16.8, 44.5, 1.2); // Círculo 8
    circulo(18.0, 43.5, 1.1); // Círculo 9
    circulo(13.5, 42.5, 1.2); // Círculo 10
    circulo(11.0, 43.0, 1.4); // Círculo 1
    circulo(12.5, 44.0, 1.3); // Círculo 2
    circulo(10.0, 44.5, 1.2); // Círculo 3
    circulo(9.0, 43.0, 1.3);  // Círculo 4
    circulo(11.5, 42.0, 1.1); // Círculo 5
    circulo(8.5, 42.5, 1.2);  // Círculo 6
    circulo(10.5, 41.5, 1.1); // Círculo 7
    circulo(12.0, 41.0, 1.3); // Círculo 8

    // Nuvem 3 (15 círculos)
    circulo(50.0, 50.0, 1.5); // Círculo 1
    circulo(51.5, 49.0, 1.4); // Círculo 2
    circulo(48.5, 50.5, 1.3); // Círculo 3
    circulo(52.0, 51.5, 1.2); // Círculo 4
    circulo(49.5, 48.0, 1.3); // Círculo 5
    circulo(51.0, 52.0, 1.1); // Círculo 6
    circulo(50.0, 53.0, 1.4); // Círculo 7
    circulo(48.0, 49.5, 1.2); // Círculo 8
    circulo(52.5, 50.0, 1.3); // Círculo 9
    circulo(50.5, 48.5, 1.1); // Círculo 10
    circulo(47.5, 50.0, 1.3); // Círculo 11
    circulo(53.0, 49.0, 1.2); // Círculo 12
    circulo(49.0, 52.0, 1.4); // Círculo 13
    circulo(48.5, 53.5, 1.2); // Círculo 14
    circulo(51.5, 54.0, 1.1); // Círculo 15

    // Nuvem 4 (5 círculos)
    circulo(70.0, 45.0, 1.8); // Círculo 1
    circulo(71.5, 46.0, 1.5); // Círculo 2
    circulo(68.5, 45.5, 1.4); // Círculo 3
    circulo(69.5, 44.5, 1.3); // Círculo 4
    circulo(72.0, 45.5, 1.2); // Círculo 5

    // Nuvem 5 (12 círculos)
    circulo(85.0, 55.0, 1.4); // Círculo 1
    circulo(86.5, 54.5, 1.2); // Círculo 2
    circulo(84.0, 56.0, 1.6); // Círculo 3
    circulo(87.0, 55.5, 1.5); // Círculo 4
    circulo(83.5, 54.0, 1.3); // Círculo 5
    circulo(86.0, 56.5, 1.1); // Círculo 6
    circulo(84.5, 55.0, 1.4); // Círculo 7
    circulo(88.0, 54.0, 1.3); // Círculo 8
    circulo(82.0, 55.5, 1.2); // Círculo 9
    circulo(88.5, 56.5, 1.1); // Círculo 10
    circulo(82.5, 57.0, 1.0); // Círculo 11
    circulo(87.5, 53.5, 1.0); // Círculo 12

    // Nuvem 6 (10 círculos)
    circulo(25.0, 60.0, 1.5); // Círculo 1
    circulo(26.5, 59.5, 1.4); // Círculo 2
    circulo(24.0, 60.5, 1.3); // Círculo 3
    circulo(27.0, 61.0, 1.2); // Círculo 4
    circulo(24.5, 59.0, 1.1); // Círculo 5
    circulo(23.5, 60.0, 1.1); // Círculo 6
    circulo(28.0, 58.5, 1.4); // Círculo 7
    circulo(24.0, 58.0, 1.2); // Círculo 8
    circulo(27.0, 59.5, 1.0); // Círculo 9
    circulo(25.5, 61.0, 1.3); // Círculo 10

    // Nuvem 7 (6 círculos)
    circulo(75.0, 40.0, 1.5); // Círculo 1
    circulo(76.0, 41.5, 1.3); // Círculo 2
    circulo(74.5, 41.0, 1.2); // Círculo 3
    circulo(77.0, 39.5, 1.4); // Círculo 4
    circulo(78.0, 40.5, 1.1); // Círculo 5
    circulo(75.5, 42.0, 1.0); // Círculo 6
}

// Função para desenhar um círculo
void circulo(float x, float y, float raio) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Centro do círculo
    for (int i = 0; i <= 100; i++) {
        float angulo = 2.0 * PI * i / 100; // Ângulo atual
        glVertex2f(x + (raio * cosf(angulo)), y + (raio * sinf(angulo))); // Desenha o vértice
    }
    glEnd();
}