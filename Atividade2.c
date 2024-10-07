#include <GL/glut.h> //O arquivo glut.h inclui, além dos protótipos das funções GLUT, os arquivos gl.h e glu.h,
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define PI 3.14159265358979323846

void circulo(float x, float y, float raio);
void desenhaMontanhas();
void display(void);


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

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT); // Limpa a janela de visualização com a cor de fundo especificada

  // Cor do Céu
  glBegin(GL_QUADS);
    // Uma cor mais clara de azul em baixo
    glColor3ub(222, 241, 255);
    glVertex2f(0, 30);
    glVertex2f(100, 30);
    // Coloca uma nova cor mais escura para o topo
    glColor3ub(152, 215, 254);
    glVertex2f(100, 60);
    glVertex2f(0, 60);
  glEnd();

  // Desenha o sol
  glColor3ub(255, 255, 102); // Cor amarelo claro
  circulo(98.0, 57.0, 6.0); // Círculo externo

  glColor3ub(255, 204, 0); // Cor amarela
  circulo(98.0, 57.0, 5.5); // Círculo central

  // Desenha montanhas
  desenhaMontanhas();

  // Desenha Areia
  glColor3ub(255, 255, 221);
  glBegin(GL_QUADS);
      glVertex2f(0.0, 0.0);   // Ponto inferior esquerdo
      glVertex2f(100.0, 0.0);  // Ponto inferior direito
      glVertex2f(100.0, 30.0); // Ponto superior direito
      glVertex2f(0.0, 30.0);  // Ponto superior esquerdo
  glEnd();


  //Desenha mar

  glColor3ub(229, 255, 254); // Cor mais clarinha
    glBegin(GL_POLYGON);
          glVertex2f(0, 0);
          glVertex2f(0, 15);
          glVertex2f(13, 17.8);
          glVertex2f(40.4, 10.6);
          glVertex2f(80, 16);
          glVertex2f(92, 12);
          glVertex2f(100, 12.7);
          glVertex2f(100, 0);
    glEnd();

    glColor3ub(85, 194, 249); // Cor mais clarinha
    glBegin(GL_POLYGON);
          glVertex2f(0, 0);
          glVertex2f(0, 12);
          glVertex2f(13, 14.8);
          glVertex2f(40.4, 7.6);
          glVertex2f(80, 13);
          glVertex2f(92, 9);
          glVertex2f(100, 9.7);
          glVertex2f(100, 0);
    glEnd();
  

  // Desenha arvores
  // Desenha gramas
  // Desenha flores

  glFlush(); 
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

void desenhaMontanhas(){
//A pontiaguda do meio
    glColor3ub(195, 216, 187); // o verde claro
      glBegin(GL_POLYGON);
        glVertex2f(20, 40);
        glVertex2f(30, 43);
        glVertex2f(65, 30);
        glVertex2f(20, 30);
        glVertex2f(20, 40);
      glEnd();
    glColor3ub(134, 166, 168); // verde escuro para fazer 'sombra'
      glBegin(GL_POLYGON);
        glVertex2f(20, 40);
        glVertex2f(30, 43);
        glVertex2f(48.6, 36);
        glVertex2f(34.9, 41);
        glVertex2f(45.1, 30);
        glVertex2f(20, 30);
        glVertex2f(20, 40);
      glEnd();

    //A redonda da esquerda
    glColor3ub(94, 120, 143); // Cor verde escuro 
    circulo(3.0, 5.0, 40.0); // Círculo da sombra

    glColor3ub(199, 219, 184); // Cor da montanha
    circulo(0.0, 3.5, 39.0); // Círculo da montanha

    //A da direita
    
    //Parte de pedra
    
    glBegin(GL_TRIANGLES);
      glColor3ub(131, 118, 136);
      glVertex2f(88, 30);
      glVertex2f(100, 50);
      glVertex2f(105, 30);
      //Pequenos triangulos internos
      glColor3ub(147, 133, 149);
      
      glVertex2f(88, 30);
      glVertex2f(91, 35.2);
      glVertex2f(94, 30);

      glVertex2f(94, 30);
      glVertex2f(97, 45);
      glVertex2f(100, 30);

      glColor3ub(127, 114, 142);
      glVertex2f(91, 35.2);
      glVertex2f(97, 45);
      glVertex2f(94, 30);
    glEnd();


    //Parte de grama
      glColor3ub(199, 219, 184);// Parte verde
        glBegin(GL_POLYGON);
          glVertex2f(65, 30);
          glVertex2f(80, 42);
          glVertex2f(88, 48.2);
          glVertex2f(90.1, 51.5);
          glVertex2f(100, 51.5);
          glVertex2f(100, 50);
          glVertex2f(97, 45);
          glVertex2f(88, 30);
        glEnd();

        glColor3ub(93, 119, 143); // Parte sombra
        glBegin(GL_POLYGON);
          glVertex2f(65, 30);
          glVertex2f(79, 42);
          glVertex2f(87.5, 38.2);
          glVertex2f(81.8, 36.3);
          glVertex2f(90.1, 33.5);
          glVertex2f(88, 30);
        glEnd();
}