#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define TRUE 1
#define FALSE 0
#define PARA_CIMA 0
#define PARA_BAIXO 180
#define PI 3.14159265358979323846

#define NUM_FLORES 10
static GLint bracoE = 0, bracoD = 0, antebracoE = 0, antebracoD = 0, maoE = 0, maoD = 0;


// Posições do braço esquerdo
float posicaoBracoX_E = 0.0; // Posição X inicial do braço esquerdo
float posicaoBracoY_E =  0.0;  // Posição Y inicial do braço esquerdo
float posicaoAntebracoX_E = 0.0;
float posicaoAntebracoY_E =  0.0;
float posicaoMaoX_E = 0.0;
float posicaoMaoY_E = 0.0;

// Posições do braço direito (inverte o eixo X para simetria)
float posicaoBracoX_D = 0.0;  // Posição X inicial do braço direito
float posicaoBracoY_D = 0.0;  // Posição Y inicial do braço direito
float posicaoAntebracoX_D = 0.0;
float posicaoAntebracoY_D = 0.0;
float posicaoMaoX_D =0.0;
float posicaoMaoY_D = 0.0;




// Definindo a estrutura para armazenar as propriedades de cada flor
typedef struct {
    float x, y;            // Posição da flor
    float anguloRotacao;   // Ângulo de rotação da flor
    float escala;          // Fator de escala (mesma para x e y)
} Flor;

// Array que armazenará as flores
Flor flores[NUM_FLORES];

// Posições iniciais e escala de Steven
float stevenPosX = 75.0; 
float stevenPosY = 29.0; 
float stevenEscala = 15.0;

//Se o escudo está ativado
int escudoAtivado = FALSE;

// Declaração de funções para desenho de elementos
void circulo(float x, float y, float raio);
void semiCirculo(float x, float y, float raio, float anguloRotacao);
void desenhaFlorClara(float x, float y, float anguloRotacao, float escala);
void desenhaFlorEscura(float x, float y, float anguloRotacao, float escala);
void desenhaFlores();
void desenhaMontanhas();
void desenhaNuvens();
void desenhaVegetacao();
void desenharStevePizza(float x, float y, float escala);
void desenharSteven(float x, float y, float escala);
void display(void);
void TeclasEspeciais(int tecla, int x, int y);
void Teclado(unsigned char tecla, int x, int y);
void Animar(int interacoes);
void animarFlores();


void inicializaFlores() {
    flores[0] = (Flor){10.0f, 50.0f, 45.0f, 1.0f};  // Flor 1
    flores[1] = (Flor){20.0f, 53.0f, 30.0f, 1.2f};  // Flor 2
    flores[2] = (Flor){30.0f, 46.0f, 60.0f, 1.1f};  // Flor 3
    flores[3] = (Flor){40.0f, 54.0f, 15.0f, 0.9f};  // Flor 4
    flores[4] = (Flor){50.0f, 51.0f, 90.0f, 1.0f};  // Flor 5
    flores[5] = (Flor){60.0f, 54.0f, 135.0f, 1.3f}; // Flor 6
    flores[6] = (Flor){70.0f, 45.0f, 20.0f, 1.0f};  // Flor 7
    flores[7] = (Flor){80.0f, 50.0f, 150.0f, 1.0f}; // Flor 8
    flores[8] = (Flor){90.0f, 47.0f, 75.0f, 1.2f};  // Flor 9
    flores[9] = (Flor){100.0f, 50.0f, 105.0f, 1.1f}; // Flor 10
}

int main(int argc, char** argv){
  // Inicialização e configuração da janela GLUT
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (1000, 600);
  glutInitWindowPosition (0, 0);
  glutCreateWindow (argv[1]);

  glClearColor(1.0, 1.0, 1.0, 0.0); // Cor de fundo (branco)
  glOrtho(0.0, 100.0, 0.0, 60.0, -1.0, 1.0); // Define a área de visualização
  glClear(GL_COLOR_BUFFER_BIT);

  inicializaFlores(); // Inicializa as flores

  // Funções callback para interação e renderização
  glutKeyboardFunc(Teclado); //Trata eventos de teclado
  glutSpecialFunc(TeclasEspeciais); 
  glutTimerFunc(30,Animar,0);
  glutDisplayFunc(display); 
  glutMainLoop(); // Loop principal da GLUT
  return 0;
}

// Função de renderização principal
void display(void) {
  glClear(GL_COLOR_BUFFER_BIT); // Limpa a tela com a cor de fundo

  // Desenha o céu com gradiente
  glBegin(GL_QUADS);
    glColor3ub(222, 241, 255); // Azul claro na base
    glVertex2f(0, 30);
    glVertex2f(100, 30);
    glColor3ub(152, 215, 254); // Azul escuro no topo
    glVertex2f(100, 60);
    glVertex2f(0, 60);
  glEnd();

  // Chama funções para desenhar componentes do cenário
  desenhaNuvens(); // Desenha as nuvens
  glColor3ub(253, 255, 231); // Amarelo do sol
  circulo(65.0, 45.0, 4.5); // Círculo central do sol
  desenhaMontanhas(); // Desenha as montanhas

  // Desenha a areia na parte inferior da tela
  glColor3ub(255, 255, 221);
  glBegin(GL_QUADS);
      glVertex2f(0.0, 0.0);
      glVertex2f(100.0, 0.0);
      glVertex2f(100.0, 30.0);
      glVertex2f(0.0, 30.0);
  glEnd();

  // Desenha o mar usando dois tons de azul
  glColor3ub(229, 255, 254);
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

  glColor3ub(85, 194, 249); // Azul mais escuro
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

  // Desenha vegetação e personagens
  desenhaVegetacao();
  desenhaFlores(); // Desenha as flores ao vento
  desenharStevePizza(60, 28, 12);
  desenharSteven(stevenPosX, stevenPosY, stevenEscala);

  glutSwapBuffers(); 
}

//Função de tratamento de eventos do teclado
void Teclado(unsigned char tecla, int x, int y){
  switch (tecla) { //quando a tecla ESC (keycode=27) for pressionada

        case 'q': bracoE += 5.0f; break; // Rotaciona braço esquerdo
        case 'a': bracoE -= 5.0f; break;

        // Movimento do antebraço esquerdo
        case 'w': antebracoE += 5.0f; break; // Rotaciona antebraço esquerdo
        case 's': antebracoE -= 5.0f; break;

        // Movimento da mão esquerda
        case 'e': maoE += 5.0f; break; // Rotaciona mão esquerda
        case 'd': maoE -= 5.0f; break;

        // Movimento do braço direito
        case 'u': bracoD += 5.0f; break; // Rotaciona braço direito
        case 'j': bracoD -= 5.0f; break;

        // Movimento do antebraço direito
        case 'i': antebracoD += 5.0f; break; // Rotaciona antebraço direito
        case 'k': antebracoD -= 5.0f; break;

        // Movimento da mão direita
        case 'o': maoD += 5.0f; break; // Rotaciona mão direita
        case 'l': maoD -= 5.0f; break;
    case 27:       //o programa deverá ser finalizado
         exit(0);
    break;

  }
  glutPostRedisplay();
}

// Função para detectar e responder a teclas de movimentação
void TeclasEspeciais(int tecla, int x, int y){
    GLfloat desloc=1;
    switch (tecla) {
      case GLUT_KEY_RIGHT:
        stevenPosX += desloc; // Move Steven para a direita
        break;
      case GLUT_KEY_LEFT:
        stevenPosX -= desloc; // Move Steven para a esquerda
        break;
      case GLUT_KEY_UP:
        stevenPosY += desloc; // Move Steven para cima
        break;
      case GLUT_KEY_DOWN:
        stevenPosY -= desloc; // Move Steven para baixo
        break;
      case GLUT_KEY_PAGE_UP:
        stevenEscala += 1; // Aumenta a escala
        break;
      case GLUT_KEY_PAGE_DOWN:
        stevenEscala -= 1; // Diminui a escala
        break;  
    }
    glutPostRedisplay(); // Redesenha a cena
}

// Função para desenhar um círculo com transformações
void circulo(float x, float y, float raio) {
    glPushMatrix(); // Salva o estado da matriz atual

    // Aplica translação e escala para o círculo
    glTranslatef(x, y, 0.0f);  
    glScalef(raio, raio, 1.0f); 

    // Desenha um círculo usando um fan de triângulos
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f); // Centro do círculo
    for (int i = 0; i <= 100; i++) {
        float angulo = 2.0 * PI * i / 100; // Ângulo Atual
        glVertex2f(cosf(angulo), sinf(angulo));
    }
    glEnd();

    glPopMatrix(); // Restaura o estado da matriz
}

// Função para desenhar um semi-círculo com transformações
void semiCirculo(float x, float y, float raio, float anguloRotacao) {
    glPushMatrix();

    // Aplica translação, escala e rotação para o semi-círculo
    glTranslatef(x, y, 0.0f);  
    glScalef(raio, raio, 1.0f); 
    glRotatef(anguloRotacao, 0.0f, 0.0f, 1.0f); 

    // Desenha o semi-círculo
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f); 
    for (int i = 0; i <= 50; i++) {
        float angulo = PI * i / 50; // Ângulo Atual
        glVertex2f(cosf(angulo), sinf(angulo));
    }
    glEnd();

    glPopMatrix();
}

// Função para desenhar todas as flores
void desenhaFlores() {
    for (int i = 0; i < NUM_FLORES; i++) {
        if (i < 5) {
            // Flores claras
            desenhaFlorClara(flores[i].x, flores[i].y, flores[i].anguloRotacao, flores[i].escala);
        } else {
            // Flores escuras
            desenhaFlorEscura(flores[i].x, flores[i].y, flores[i].anguloRotacao, flores[i].escala);
        }
    }
}

// Função para desenhar uma cena de montanhas com diferentes formas e texturas.
void desenhaMontanhas(){
    // Montanha pontiaguda do meio
    glColor3ub(195, 216, 187); // Verde claro para o corpo principal da montanha
    glBegin(GL_POLYGON);
      glVertex2f(20, 40); // Ponto superior esquerdo
      glVertex2f(30, 43); // Ponto superior central, formando o pico
      glVertex2f(65, 30); // Ponto inferior direito
      glVertex2f(20, 30); // Ponto inferior esquerdo, fechando a base
    glEnd();

    glColor3ub(134, 166, 168); // Verde escuro para criar uma 'sombra' na montanha
    glBegin(GL_POLYGON);
      glVertex2f(20, 40); // Ponto inicial (superior esquerdo)
      glVertex2f(30, 43); // Ponto superior, o pico
      glVertex2f(48.6, 36); // Ponto de sombra no meio direito
      glVertex2f(34.9, 41); // Ponto intermediário esquerdo
      glVertex2f(45.1, 30); // Ponto inferior direito
      glVertex2f(20, 30); // Base da sombra
    glEnd();

    // Montanha redonda à esquerda
    glColor3ub(94, 120, 143); // Verde escuro para a sombra da montanha redonda
    circulo(3.0, 5.0, 40.0); // Desenha um círculo para formar a sombra

    glColor3ub(199, 219, 184); // Cor da montanha principal
    circulo(0.0, 3.5, 39.0); // Desenha a montanha com um círculo sobreposto

    // Montanha à direita com detalhes de pedra e grama

    // Parte de pedra - Triângulos formando uma aparência rochosa
    glBegin(GL_TRIANGLES);
      glColor3ub(131, 118, 136); // Cinza para o corpo principal da pedra
      glVertex2f(88, 30); // Base esquerda
      glVertex2f(100, 50); // Ponto superior central
      glVertex2f(105, 30); // Base direita

      // Pequenos triângulos internos para textura
      glColor3ub(147, 133, 149); // Cinza mais claro para um triângulo interno
      glVertex2f(88, 30); // Base esquerda
      glVertex2f(91, 35.2); // Ponto médio superior esquerdo
      glVertex2f(94, 30); // Base central

      glVertex2f(94, 30); // Base central
      glVertex2f(97, 45); // Ponto superior central
      glVertex2f(100, 30); // Base direita

      glColor3ub(127, 114, 142); // Cinza escuro para triângulo adicional
      glVertex2f(91, 35.2); // Ponto médio superior esquerdo
      glVertex2f(97, 45); // Ponto superior
      glVertex2f(94, 30); // Base central
    glEnd();

    // Parte de grama no topo da montanha
    glColor3ub(199, 219, 184); // Verde para a grama no topo da montanha
    glBegin(GL_POLYGON);
      glVertex2f(65, 30); // Base esquerda da grama
      glVertex2f(80, 42); // Ponto intermediário esquerdo
      glVertex2f(88, 48.2); // Curva superior esquerda
      glVertex2f(90.1, 51.5); // Curva superior central
      glVertex2f(100, 51.5); // Extremo direito superior
      glVertex2f(100, 50); // Ligeira queda à direita
      glVertex2f(97, 45); // Ponto médio da montanha
      glVertex2f(88, 30); // Base direita da grama
    glEnd();

    // Parte de sombra da grama
    glColor3ub(93, 119, 143); // Verde escuro para sombra na grama
    glBegin(GL_POLYGON);
      glVertex2f(65, 30); // Base esquerda da sombra
      glVertex2f(79, 42); // Ponto intermediário esquerdo
      glVertex2f(87.5, 38.2); // Ponto curvo à direita
      glVertex2f(81.8, 36.3); // Curva intermediária esquerda
      glVertex2f(90.1, 33.5); // Curva inferior direita
      glVertex2f(88, 30); // Base direita da sombra
    glEnd();
}

// Função para desenhar uma nuvem com base em dois semi-círculos e aplicar transformações de posição, rotação e escala.
void desenhaNuvem2(float x, float y, float escala, float anguloRotacao, int inverte) {
    glPushMatrix();  // Salva a transformação

    // Aplica a tradução, rotação e escala
    glTranslatef(x, y, 0.0f);
    glRotatef(anguloRotacao, 0.0f, 0.0f, 1.0f);
    glScalef(escala, escala, 1.0f);

    if(inverte) glScalef(-1.0f, 1.0f, 1.0f);  // Reflete no eixo X

    // Desenha os dois semi-círculos
    glColor3ub(255, 255, 255);  
    semiCirculo(-2.5f, 0.0f, 3.0f, PARA_CIMA);  // Esquerdo
    semiCirculo(2.5f, 0.0f, 4.0f, PARA_CIMA);   // Direito

    glPopMatrix();  // Restaura a transformação
}

// Função para desenhar uma nuvem com três semi-círculos e aplicar transformações de posição, rotação e escala.
void desenhaNuvem3(float x, float y, float escala, float anguloRotacao) {
    glPushMatrix();  // Salva a transformação

    // Aplica a tradução, rotação e escala
    glTranslatef(x, y, 0.0f);
    glRotatef(anguloRotacao, 0.0f, 0.0f, 1.0f);
    glScalef(escala, escala, 1.0f);

    // Desenha os três semi-círculos
    glColor3ub(255, 255, 255);  
    semiCirculo(-4.0f, 0.0f, 3.0f, PARA_CIMA);  // Esquerdo
    semiCirculo(0.0f, 0.0f, 4.0f, PARA_CIMA);   // Central
    semiCirculo(4.0f, 0.0f, 3.0f, PARA_CIMA);   // Direito

    glPopMatrix();  // Restaura a transformação
}

// Função para desenhar o céu com nuvens e listras, incluindo nuvens sombreadas e mini nuvens.
void desenhaNuvens() {
  // Listras no céu
  glBegin(GL_TRIANGLES);
    glColor3ub(176, 225, 255);  
    glVertex2f(0, 60); glVertex2f(5, 60); glVertex2f(0, 45);
    glVertex2f(100, 60); glVertex2f(100, 45); glVertex2f(85, 60);
    glVertex2f(55, 60); glVertex2f(56, 60); glVertex2f(52, 50);
    glVertex2f(23, 60); glVertex2f(26, 60); glVertex2f(19, 50);
  glEnd();

  // Nuvem sombreada
  glColor3ub(210, 231, 236);  
  semiCirculo(9.8, 53.5, 2.5, PARA_BAIXO);  
  semiCirculo(15.2, 53.5, 2.5, PARA_BAIXO); 

  glColor3ub(255, 255, 255);  
  semiCirculo(10, 52.5, 2.5, PARA_CIMA);  
  semiCirculo(15, 52.5, 2.5, PARA_CIMA); 

  // Base quadrada da sombra
  glBegin(GL_QUADS);
    glColor3ub(210, 231, 236);  
    glVertex2f(10.0, 51); glVertex2f(15, 51); glVertex2f(15, 53.5); glVertex2f(10, 53.5);
    glColor3ub(255, 255, 255);  
    glVertex2f(10.0, 52.5); glVertex2f(15, 52.5); glVertex2f(15, 55); glVertex2f(10, 55);
  glEnd();

  // Desenha as nuvens em posições variadas
  desenhaNuvem2(6.5, 44, 1, 0, TRUE);  
  desenhaNuvem2(35, 50, 2, 0, FALSE);  
  desenhaNuvem2(45.2, 35.3, 1.0, 0, TRUE);  
  desenhaNuvem2(65, 35, 0.75, 0, FALSE);  
  desenhaNuvem2(89, 48, 2, 0, FALSE);  
  desenhaNuvem3(75, 55, 0.3, 0);  

  // Mini nuvens
  glColor3ub(255, 255, 255);  
  circulo(3, 59, 0.4);  
  circulo(1, 57, 0.4);  
  semiCirculo(20, 45.7, 0.4, PARA_CIMA);  
  semiCirculo(22, 46, 0.6, PARA_CIMA);  
  semiCirculo(50, 56, 0.7, PARA_CIMA);  
  semiCirculo(90, 57, 0.7, PARA_CIMA);  
  circulo(98, 56, 0.5);  
  semiCirculo(40, 46, 0.7, PARA_CIMA);  
}

// Desenha a grama no ponto (x, y)
void desenhaGrama(float x, float y){
  glColor3ub(155, 181, 147);  // Cor verde da grama
  glPushMatrix();  // Salva a transformação

  // Translada a posição da grama
  glTranslatef(x, y, 0);

  // Desenha três semi-círculos de grama
  semiCirculo(0, 0, 1.5, PARA_CIMA);   
  semiCirculo(-1.5, 0, 1, PARA_CIMA);  
  semiCirculo(1.5, 0, 0.8, PARA_CIMA); 

  glPopMatrix();  // Restaura a transformação
}

// Desenha a flor clara no ponto (x, y) com rotação e escala uniforme
void desenhaFlorClara(float x, float y, float anguloRotacao, float escala) {
  glPushMatrix(); // Salva o estado atual da transformação

  // Translada para o centro da flor e aplica a rotação
  glTranslatef(x, y, 0.0f);
  glRotatef(anguloRotacao, 0.0f, 0.0f, 1.0f); // Rotaciona as pétalas
  glScalef(escala, escala, 1.0f);  // Aplica a escala uniforme (mesmo valor para X e Y)

  // Pétalas da flor em rosa claro
  glColor3ub(243, 154, 181);
  circulo(0.0f, 0.7f, 0.7f);  // Superior
  circulo(0.0f, -0.7f, 0.7f); // Inferior
  circulo(-0.7f, 0.0f, 0.7f); // Esquerda
  circulo(0.7f, 0.0f, 0.7f);  // Direita

  // Meio da flor em rosa escuro
  glColor3ub(237, 86, 155);
  circulo(0.0f, 0.0f, 0.3f); // Centro da flor

  glPopMatrix(); // Restaura o estado anterior
}

// Desenha a flor escura no ponto (x, y) com rotação e escala uniforme
void desenhaFlorEscura(float x, float y, float anguloRotacao, float escala) {
  glPushMatrix(); // Salva o estado atual da transformação

  // Translada para o centro da flor e aplica a rotação
  glTranslatef(x, y, 0.0f);
  glRotatef(anguloRotacao, 0.0f, 0.0f, 1.0f); // Rotaciona as pétalas
  glScalef(escala, escala, 1.0f);  // Aplica a escala uniforme (mesmo valor para X e Y)

  // Pétalas da flor em rosa médio
  glColor3ub(242, 137, 155);
  circulo(-0.7f, 0.0f, 0.7f);  // Esquerda
  circulo(0.7f, 0.0f, 0.7f);   // Direita
  circulo(0.0f, 0.7f, 0.7f);   // Superior
  circulo(0.0f, -0.7f, 0.7f);  // Inferior

  // Meio da flor em rosa escuro
  glColor3ub(237, 86, 155);
  circulo(0.0f, 0.0f, 0.3f); // Centro da flor

  glPopMatrix(); // Restaura o estado anterior
}

// Desenha vegetação, incluindo grama e flores nas montanhas
void desenhaVegetacao() {
  // Grama nas montanhas
  desenhaGrama(5, 33);
  desenhaGrama(9, 37);
  desenhaGrama(15, 31);
  desenhaGrama(78, 35);
  desenhaGrama(90, 39);
  desenhaGrama(85, 43);
  desenhaGrama(49, 30);
  desenhaGrama(38, 30);
  desenhaGrama(32, 36);

  // Flores na montanha direita
  desenhaFlorClara(90, 43, 0, 1);  // Flor clara
  desenhaFlorEscura(85, 32, 45, 1); // Flor escura
  desenhaFlorEscura(72, 34, 45, 1); // Flor escura
  desenhaFlorEscura(80, 40, 45, 1); // Flor escura

  // Flores na montanha do meio
  desenhaFlorClara(45, 34, 0, 1);  // Flor clara
  desenhaFlorClara(54, 32, 0, 1);  // Flor clara
  desenhaFlorEscura(30, 40, 45, 1); // Flor escura
  desenhaFlorEscura(37, 35, 45, 1); // Flor escura

  // Flores na montanha da esquerda
  desenhaFlorClara(10, 32, 0, 1);  // Flor clara
  desenhaFlorClara(21, 33, 0, 1);  // Flor clara
  desenhaFlorClara(3, 38, 0, 1);   // Flor clara
  desenhaFlorClara(15, 36, 0, 1);  // Flor clara
  desenhaFlorEscura(5, 43.5, 45, 1); // Flor escura
  desenhaFlorEscura(18, 40, 45, 1); // Flor escura
  desenhaFlorEscura(29, 33, 45, 1); // Flor escura
}

// Função que desenha o StevePizza no ponto (x, y) com escala
void desenharStevePizza(float x, float y, float escala) {
    glPushMatrix();  // Salva a transformação atual (posição e escala)
    
    // Translada a fatia de pizza para a posição (x, y) e aplica a escala
    glTranslatef(x, y, 0.0f);  
    glScalef(escala, escala, 1.0f);  

    // Desenha a borda alaranjada da pizza (casca)
    glColor3f(1.0, 0.5, 0.0);  
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.2, 0.4);  
    glVertex2f(0.0, 0.4);   
    glVertex2f(0.0, -0.4);  
    glEnd();

    // Desenha a parte interna amarela da pizza
    glColor3f(1.0, 0.9, 0.3);  
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.18, 0.38);  
    glVertex2f(0.18, 0.38);   
    glVertex2f(0.0, -0.35);   
    glEnd();

    // Desenha a borda recheada no topo da pizza
    glColor3f(1.0, 0.7, 0.2);  
    glBegin(GL_QUADS);
    glVertex2f(-0.2, 0.35);   
    glVertex2f(0.19, 0.35);    
    glVertex2f(0.14, 0.45);   
    glVertex2f(-0.25, 0.45);  
    glEnd();

    // Desenha os óculos escuros (lentes)
    glColor3f(0.0, 0.0, 0.0);  // Cor preta dos óculos
    glBegin(GL_QUADS);
    glVertex2f(-0.1, 0.15);  
    glVertex2f(0.01, 0.15);  
    glVertex2f(0.01, 0.10);  
    glVertex2f(-0.1, 0.10);  
    glEnd();
    
    // Lente direita dos óculos
    float desvioX = 0.15;  
    glBegin(GL_QUADS);
    glVertex2f(-0.1 + desvioX, 0.15);
    glVertex2f(0.01 + desvioX, 0.15);
    glVertex2f(0.01 + desvioX, 0.10);
    glVertex2f(-0.1 + desvioX, 0.10);
    glEnd();

    // Desenha as lentes dos óculos (semi-círculos)
    semiCirculo(-0.04, 0.15, 0.08, 180);  
    semiCirculo(0.1, 0.15, 0.08, 180);  

    // Desenha a perna do óculos (parte do suporte)
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(-0.15, 0.13);  
    glVertex2f(-0.1, 0.13);  
    glVertex2f(-0.1, 0.11);  
    glVertex2f(-0.15, 0.11);  
    glEnd();

    // Desenha o sorriso (contorno superior com um semi-círculo)
    glColor3f(0.0, 0.0, 0.0);  
    glBegin(GL_LINE_STRIP);  // Sorriso desenhado com linhas
    for (int i = 0; i <= 100; i++) {
        float teta = PI * i / 100;
        glVertex2f(0.05 * cos(teta), -0.03 * sin(teta));
    }
    glEnd();

    // Desenha a parte interna da boca (preenchida)
    glColor3f(0.0, 0.0, 0.0);  
    glBegin(GL_TRIANGLE_FAN);  // Boca preenchida
    glVertex2f(0.0, 0.0);  
    for (int i = 0; i <= 100; i++) {
        float teta = PI * i / 100;
        glVertex2f(0.05 * cos(teta), -0.03 * sin(teta));
    }
    glEnd();

    // Desenha a língua (vermelha)
    glColor3f(1.0, 0.0, 0.0);  
    glBegin(GL_TRIANGLE_FAN);  // Língua preenchida
    glVertex2f(0.0, -0.01);  
    for (int i = 0; i <= 100; i++) {
        float teta = PI * i / 100;
        glVertex2f(0.03 * cos(teta), -0.01 - 0.015 * sin(teta));
    }
    glEnd();

    glPopMatrix();  // Restaura a transformação original
}

// Função para desenhar um retângulo simples
// Recebe as coordenadas (x1, y1) e (x2, y2) para as extremidades do retângulo
void desenharRetangulo(float x1, float y1, float x2, float y2) {
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}

// Função para desenhar um retângulo com bordas arredondadas
// Recebe as coordenadas (x1, y1) e (x2, y2) do retângulo, e o raio das bordas arredondadas
void desenharRetanguloArredondado(float x1, float y1, float x2, float y2, float raio) {
    // Ajuste o raio para garantir que ele não ultrapasse o tamanho do retângulo
    float comprimento = x2 - x1;
    float altura = y2 - y1;

    // Limita o raio para não ser maior que metade da largura ou altura do retângulo
    if (raio > comprimento / 2) raio = comprimento / 2;
    if (raio > altura / 2) raio = altura / 2;

    // Desenhar o retângulo central sem as bordas arredondadas
    glBegin(GL_QUADS);
    glVertex2f(x1 + raio, y1);
    glVertex2f(x2 - raio, y1);
    glVertex2f(x2 - raio, y2);
    glVertex2f(x1 + raio, y2);
    glEnd();

    // Desenhar os círculos nas bordas para arredondar
    circulo(x1 + raio, y1 + raio, raio);  // Canto inferior esquerdo
    circulo(x2 - raio, y1 + raio, raio);  // Canto inferior direito
    circulo(x1 + raio, y2 - raio, raio);  // Canto superior esquerdo
    circulo(x2 - raio, y2 - raio, raio);  // Canto superior direito

    // Desenhar os retângulos nas laterais para completar o arredondamento
    desenharRetangulo(x1, y1 + raio, x1 + raio, y2 - raio);  // Lateral esquerda
    desenharRetangulo(x2 - raio, y1 + raio, x2, y2 - raio);  // Lateral direita
}

// Função para desenhar uma estrela com 5 pontas no ponto (x,y)
void desenharEstrela(float x, float y) {
    glPushMatrix(); // Salva o estado atual da matriz

    // Translada para a posição da estrela
    glTranslatef(x, y, 0.0f);
    // Rotaciona 15 graus para a esquerda (sentido anti-horário)
    glRotatef(15.0f, 0.0f, 0.0f, 1.0f);

    glBegin(GL_TRIANGLE_FAN);

    // Definindo o centro da estrela no ponto de origem (0, 0) depois da translação
    glVertex2f(0.0f, 0.0f); // Centro da estrela

    // Vértices da estrela
    for (int i = 0; i <= 10; i++) {
        // Cálculo do ângulo de cada ponto
        float angulo = i * 2 * PI / 10; // 10 vértices (5 pontas)

        // Raio da estrela
        float raio = (i % 2 == 0) ? 0.07 : 0.02; // Raio maior ou menor

        // Coordenadas dos pontos da estrela (sem translação)
        float x = raio * cos(angulo);
        float y = raio * sin(angulo);

        glVertex2f(x, y); // Adiciona o vértice rotacionado e transladado
    }

    glEnd();

    glPopMatrix(); // Restaura o estado anterior da matriz
}
void desenhaBracoERosa(){

    // Braços (divididos em braço e antebraço)
      glColor3ub(255, 187, 255); // Cor da pele

    // Braço esquerdo superior
    desenharRetanguloArredondado(-0.189, 0.35, -0.09999, 0.5, 0.02); 
    // Mangas (ajuste a posição e tamanho)
    glColor3ub(253, 112, 249); // Cor rosada da manga
     desenharRetanguloArredondado(-0.19, 0.4, -0.08, 0.5, 0.02); // Manga esquerda arredondada

}

void desenhaAntebracoERosa(){

    glColor3ub(255, 187, 255); // Cor da pele

    // Braço esquerdo - antebraço
      desenharRetanguloArredondado(-0.18, 0.2, -0.1, 0.4, 0.02); 

}

void desenhaMaoERosa(){

  glColor3ub(255, 187, 255); // Cor da pele

  // Mão esquerda (círculo)
      glBegin(GL_POLYGON);
      for (int i = 0; i < 100; i++) {
          float theta = 2.0f * 3.1415926f * i / 100;
          float x = 0.05 * cosf(theta);
          float y = 0.05 * sinf(theta);
          glVertex2f(x - 0.14, y + 0.2); 
      }
      glEnd();
}

void desenhaBracoDRosa(){

    glColor3ub(255, 187, 255); // Cor da pele
    // Braço direito superior
    desenharRetanguloArredondado(0.09999, 0.35, 0.189, 0.5, 0.02); 

    glColor3ub(253, 112, 249); // Cor rosada da manga
    desenharRetanguloArredondado(0.08, 0.4, 0.19, 0.5, 0.02);   // Manga direita arredondada

}

void desenhaAntebracoDRosa(){

    glColor3ub(255, 187, 255); // Cor da pele
    // Braço direito - antebraço
    desenharRetanguloArredondado(0.1, 0.2, 0.18, 0.4, 0.02); 

}

void desenhaMaoDRosa(){

  glColor3ub(255, 187, 255); // Cor da pele
  // Mão direita (círculo)
      glBegin(GL_POLYGON);
      for (int i = 0; i < 100; i++) {
          float theta = 2.0f * 3.1415926f * i / 100;
          float x = 0.05 * cosf(theta);
          float y = 0.05 * sinf(theta);
          glVertex2f(x + 0.14, y + 0.2); 
      }
      glEnd();

}
void desenhaBracoE(){

    // Braços (divididos em braço e antebraço)
      glColor3f(1.0, 0.8, 0.6); // Cor da pele

    // Braço esquerdo superior
    desenharRetanguloArredondado(-0.189, 0.35, -0.09999, 0.5, 0.02); 
    // Mangas (ajuste a posição e tamanho)
    glColor3f(1.0, 0.5, 0.5); // Cor rosada da manga
     desenharRetanguloArredondado(-0.19, 0.4, -0.08, 0.5, 0.02); // Manga esquerda arredondada

}

void desenhaAntebracoE(){

    glColor3f(1.0, 0.8, 0.6); // Cor da pele

    // Braço esquerdo - antebraço
      desenharRetanguloArredondado(-0.18, 0.2, -0.1, 0.4, 0.02); 

}

void desenhaMaoE(){

  glColor3f(1.0, 0.8, 0.6); // Cor da pele

  // Mão esquerda (círculo)
      glBegin(GL_POLYGON);
      for (int i = 0; i < 100; i++) {
          float theta = 2.0f * 3.1415926f * i / 100;
          float x = 0.05 * cosf(theta);
          float y = 0.05 * sinf(theta);
          glVertex2f(x - 0.14, y + 0.2); 
      }
      glEnd();
}

void desenhaBracoD(){

    glColor3f(1.0, 0.8, 0.6); // Cor da pele
    // Braço direito superior
    desenharRetanguloArredondado(0.09999, 0.35, 0.189, 0.5, 0.02); 

    glColor3f(1.0, 0.5, 0.5); // Cor rosada da manga
    desenharRetanguloArredondado(0.08, 0.4, 0.19, 0.5, 0.02);   // Manga direita arredondada

}

void desenhaAntebracoD(){

    glColor3f(1.0, 0.8, 0.6); // Cor da pele
    // Braço direito - antebraço
    desenharRetanguloArredondado(0.1, 0.2, 0.18, 0.4, 0.02); 

}

void desenhaMaoD(){

  glColor3f(1.0, 0.8, 0.6); // Cor da pele
  // Mão direita (círculo)
      glBegin(GL_POLYGON);
      for (int i = 0; i < 100; i++) {
          float theta = 2.0f * 3.1415926f * i / 100;
          float x = 0.05 * cosf(theta);
          float y = 0.05 * sinf(theta);
          glVertex2f(x + 0.14, y + 0.2); 
      }
      glEnd();

}


//Função para desenha o Steven Universo
void desenharSteven(float x, float y, float escala) {
     // Aplicando translação e escala
    glPushMatrix(); // Salva o estado atual da matriz de transformação

    // Posiciona o ponto de referência para a escala
    glTranslatef(x, y, 0.0);           // Translação para a coordenada desejada (x, y)
    glScalef(escala, escala, 1.0);     // Aplica a escala proporcionalmente ao personagem
    glTranslatef(0.0, -0.36, 0.0);     // Ajuste da translação para centralizar o personagem
    
    if (y > 30) { // Condicional para determinar a aparência do personagem com base na coordenada y

        // Corpo (retângulo arredondado)
        glColor3ub(253, 112, 249); // Cor rosada para a camiseta
        desenharRetanguloArredondado(-0.1, 0.1, 0.1, 0.5, 0.05); // Corpo com bordas arredondadas

        // Círculos de transição manga-corpo
        glColor3ub(253, 112, 249); // Rosa para os círculos
        circulo(-0.085, 0.46, 0.05); // Circulo de transição esquerdo
        circulo(0.085, 0.46, 0.05); // Circulo de transição direito

        // Cabelo
        glColor3ub(254, 86, 255); // Cor do cabelo
        circulo(-0.08, 0.62, 0.08); // Mecha esquerda
        circulo(0.08, 0.62, 0.08);  // Mecha espelhada no lado direito

        // Cabeça (círculo)
        glColor3ub(255, 187, 255); // Cor da pele
        circulo(0.0, 0.6, 0.12); // Cabeça

        // Orelha
        glColor3ub(255, 187, 255); // Cor da pele para a orelha
        circulo(-0.12, 0.62, 0.03); // Orelha esquerda
        circulo(0.12, 0.62, 0.03); // Orelha direita

        // Cabelo (círculos)
        glColor3ub(255, 86, 255); // Cor do cabelo
        circulo(0.0, 0.74, 0.08); // Círculo central
        circulo(0.0, 0.78, 0.08); // Círculo central superior
        circulo(-0.07, 0.75, 0.07); // Círculo esquerdo
        circulo(0.07, 0.75, 0.07); // Círculo direito
        circulo(-0.1, 0.69, 0.06); // Círculo mais à esquerda
        circulo(0.1, 0.69, 0.06); // Círculo mais à direita
        circulo(-0.11, 0.67, 0.05); // Detalhes do cabelo
        circulo(0.11, 0.67, 0.05); // Detalhes do cabelo

        // Sobrancelhas
        glColor3ub(255, 86, 255); // Cor do cabelo para as sobrancelhas
        semiCirculo(0.05, 0.625, 0.025, 1); // Sobrancelha direita
        semiCirculo(-0.05, 0.625, 0.025, 1); // Sobrancelha esquerda

        // Olhos
        glColor3ub(252, 251, 254); // Branco dos olhos
        circulo(-0.05, 0.58, 0.035); // Olho esquerdo
        circulo(0.05, 0.58, 0.035);  // Olho direito

        // Pupilas
        glColor3ub(223, 83, 205); // Pupilas rosa
        circulo(-0.05, 0.58, 0.013); // Pupila esquerda
        circulo(0.05, 0.58, 0.013);  // Pupila direita

        // Boca
        glColor3ub(223, 83, 205); // Cor da boca (rosa)
        glBegin(GL_LINES);
            glVertex2f(-0.06, 0.52); // Ponto inicial da linha da boca
            glVertex2f(0.06, 0.52);  // Ponto final da linha da boca
        glEnd();

       /*
        // Braços (divididos em braço e antebraço)
        glColor3ub(255, 187, 255); // Cor da pele

        // Braço esquerdo superior
        desenharRetanguloArredondado(-0.189, 0.35, -0.09999, 0.5, 0.02); 

        // Braço esquerdo - antebraço
        desenharRetanguloArredondado(-0.18, 0.2, -0.1, 0.4, 0.02); 

        // Mão esquerda (círculo)
        glBegin(GL_POLYGON);
        for (int i = 0; i < 100; i++) {
            float theta = 2.0f * 3.1415926f * i / 100;
            float x = 0.05 * cosf(theta);
            float y = 0.05 * sinf(theta);
            glVertex2f(x - 0.14, y + 0.2); 
        }
        glEnd();

        // Braço direito superior
        desenharRetanguloArredondado(0.09999, 0.35, 0.189, 0.5, 0.02); 

        // Braço direito - antebraço
        desenharRetanguloArredondado(0.1, 0.2, 0.18, 0.4, 0.02); 

        // Mão direita (círculo)
        glBegin(GL_POLYGON);
        for (int i = 0; i < 100; i++) {
            float theta = 2.0f * 3.1415926f * i / 100;
            float x = 0.05 * cosf(theta);
            float y = 0.05 * sinf(theta);
            glVertex2f(x + 0.14, y + 0.2); 
        }
        glEnd();

        // Mangas (ajuste a posição e tamanho)
        glColor3ub(253, 112, 249); // Cor rosada da manga
        desenharRetanguloArredondado(-0.19, 0.4, -0.08, 0.5, 0.02); // Manga esquerda arredondada
        desenharRetanguloArredondado(0.08, 0.4, 0.19, 0.5, 0.02);   // Manga direita arredondada
      */

        desenhaBracoERosa();
        desenhaAntebracoERosa();
        desenhaMaoERosa();
        desenhaBracoDRosa();
        desenhaAntebracoDRosa();
        desenhaMaoDRosa();

        // Pernas
        glColor3ub(252, 73, 222); // Cor da calça
        desenharRetanguloArredondado(-0.1, -0.05, 0.0, 0.2, 0.02); // Perna esquerda
        desenharRetanguloArredondado(0.0, -0.05, 0.1, 0.2, 0.02); // Perna direita

        // Ajuste na roupinha
        glColor3ub(253, 112, 249); // Cor do corpo (camiseta)
        circulo(0.0, 0.25, 0.1005); // Círculo para cobrir o início das calças

        // Sandálias
        glColor3ub(255, 106, 241); // Cor das sandálias
        desenharRetanguloArredondado(-0.07, -0.04, -0.03, -0.07, 0.01); // Sandália esquerda
        desenharRetanguloArredondado(0.03, -0.04, 0.07, -0.07, 0.01);  // Sandália direita

        // Estrela
        glColor3ub(252, 251, 254); // Cor da estrela (branco)
        desenharEstrela(0.0, 0.36); // Desenha a estrela acima do personagem
    }
    else {
      // Corpo (retângulo arredondado)
      glColor3f(1.0, 0.5, 0.5); // Cor rosada para a camiseta
      desenharRetanguloArredondado(-0.1, 0.1, 0.1, 0.5, 0.05); // Corpo com bordas arredondadas

      // Círculos de transição manga-corpo
      glColor3f(1.0, 0.5, 0.5); // Cor rosa para os círculos de transição
      circulo(-0.085, 0.46, 0.05); // Círculo de transição entre corpo e manga esquerda
      circulo(0.085, 0.46, 0.05); // Círculo de transição entre corpo e manga direita

      // Cabelo
      glColor3f(0.0, 0.0, 0.0); // Cor preta para o cabelo
      circulo(-0.08, 0.62, 0.08); // Mecha de cabelo esquerda
      circulo(0.08, 0.62, 0.08);  // Mecha de cabelo direita (espelhada)

      // Cabeça (círculo)
      glColor3f(1.0, 0.8, 0.6); // Cor da pele para a cabeça
      circulo(0.0, 0.6, 0.12); // Desenha a cabeça

      // Orelhas
      glColor3f(1.0, 0.8, 0.6); // Cor da pele para as orelhas
      circulo(-0.12, 0.62, 0.03); // Orelha esquerda
      circulo(0.12, 0.62, 0.03); // Orelha direita

      // Cabelos adicionais (círculos)
      glColor3f(0.0, 0.0, 0.0); // Cor do cabelo
      circulo(0.0, 0.74, 0.08); // Círculo superior central de cabelo
      circulo(0.0, 0.78, 0.08); // Círculo superior central de cabelo
      circulo(-0.07, 0.75, 0.07); // Círculo lateral esquerdo do cabelo
      circulo(0.07, 0.75, 0.07); // Círculo lateral direito do cabelo
      circulo(-0.1, 0.69, 0.06); // Círculo inferior esquerdo do cabelo
      circulo(0.1, 0.69, 0.06); // Círculo inferior direito do cabelo
      circulo(-0.11, 0.67, 0.05); // Círculo inferior mais à esquerda
      circulo(0.11, 0.67, 0.05); // Círculo inferior mais à direita

      // Sobrancelhas (semi-círculos)
      glColor3f(0.0, 0.0, 0.0); // Cor preta para as sobrancelhas
      semiCirculo(0.05, 0.625, 0.025, 1); // Sobrancelha direita
      semiCirculo(-0.05, 0.625, 0.025, 1); // Sobrancelha esquerda

      // Olhos (ajustados em y)
      glColor3f(1.0, 1.0, 1.0); // Cor branca para os olhos
      circulo(-0.05, 0.58, 0.035); // Olho esquerdo
      circulo(0.05, 0.58, 0.035);  // Olho direito

      // Pupilas (ajustadas em y)
      glColor3f(0.0, 0.0, 0.0); // Cor preta para as pupilas
      circulo(-0.05, 0.58, 0.013); // Pupila esquerda
      circulo(0.05, 0.58, 0.013);  // Pupila direita

      // Contorno superior da boca (semicírculo)
      glColor3f(0.0, 0.0, 0.0); // Cor do contorno da boca
      glBegin(GL_LINE_STRIP);
      for (int i = 0; i <= 100; i++) {
          float teta = PI * i / 100; // Ângulo para desenhar o semicírculo
          float x = 0.05 * cos(teta);  // Raio maior para a largura do sorriso
          float y = 0.03 * sin(teta);  // Raio menor para a altura do sorriso
          glVertex2f(x, 0.52 - y);      // Ajusta a posição da boca verticalmente
      }
      glEnd();

      // Parte interna da boca (preenchimento)
      glColor3f(0.5, 0.0, 0.0); // Cor do interior da boca (vermelho escuro)
      glBegin(GL_TRIANGLE_FAN);
      glVertex2f(0.0, 0.51);  // Centro do preenchimento da boca
      for (int i = 0; i <= 100; i++) {
          float teta = PI * i / 100; // Ângulo para o semicírculo interno
          float x = 0.05 * cos(teta);  // Raio maior
          float y = 0.03 * sin(teta);  // Raio menor
          glVertex2f(x, 0.51 - y);      // Posiciona o preenchimento da boca
      }
      glEnd();

      // Dentes (semicírculo branco)
      glColor3f(1.0, 1.0, 1.0); // Cor branca para os dentes
      glBegin(GL_TRIANGLE_FAN);
      glVertex2f(0.0, 0.52);  // Centro dos dentes
      for (int i = 0; i <= 100; i++) {
          float teta = PI * i / 100; // Ângulo para os dentes
          float x = 0.04 * cos(teta);  // Raio dos dentes
          float y = 0.02 * sin(teta);  // Ajuste na altura dos dentes
          glVertex2f(x, 0.52 - y);      // Posiciona os dentes
      }
      glEnd();

      /*
      // Braços (divididos em braço e antebraço)
      glColor3f(1.0, 0.8, 0.6); // Cor da pele

      // Braço esquerdo superior
      desenharRetanguloArredondado(-0.189, 0.35, -0.09999, 0.5, 0.02); 

      // Braço esquerdo - antebraço
      desenharRetanguloArredondado(-0.18, 0.2, -0.1, 0.4, 0.02); 

      // Mão esquerda (círculo)
      glBegin(GL_POLYGON);
      for (int i = 0; i < 100; i++) {
          float theta = 2.0f * 3.1415926f * i / 100;
          float x = 0.05 * cosf(theta);
          float y = 0.05 * sinf(theta);
          glVertex2f(x - 0.14, y + 0.2); 
      }
      glEnd();

      // Braço direito superior
      desenharRetanguloArredondado(0.09999, 0.35, 0.189, 0.5, 0.02); 

      // Braço direito - antebraço
      desenharRetanguloArredondado(0.1, 0.2, 0.18, 0.4, 0.02); 

      // Mão direita (círculo)
      glBegin(GL_POLYGON);
      for (int i = 0; i < 100; i++) {
          float theta = 2.0f * 3.1415926f * i / 100;
          float x = 0.05 * cosf(theta);
          float y = 0.05 * sinf(theta);
          glVertex2f(x + 0.14, y + 0.2); 
      }
      glEnd();

      // Mangas (ajuste a posição e tamanho)
      glColor3f(1.0, 0.5, 0.5); // Cor rosada da manga
      desenharRetanguloArredondado(-0.19, 0.4, -0.08, 0.5, 0.02); // Manga esquerda arredondada
      desenharRetanguloArredondado(0.08, 0.4, 0.19, 0.5, 0.02);   // Manga direita arredondada

      */

      /*
      desenhaBracoE();
      desenhaAntebracoE();
      desenhaMaoE();
      desenhaBracoD();
      desenhaAntebracoD();
      desenhaMaoD();

      */

      glPushMatrix();
        // Transforma o braço (pai)
        glTranslatef(posicaoBracoX_E, posicaoBracoY_E, 0); // Translação do braço
        glRotatef(bracoE, 0, 0, 1);               // Rotação do braço

        desenhaBracoE();

        glPushMatrix();
            // Transforma o antebraço (intermediário)
            glTranslatef(posicaoAntebracoX_E, posicaoAntebracoY_E, 0); // Translação do antebraço
            glRotatef(antebracoE, 0, 0, 1);                   // Rotação do antebraço

            desenhaAntebracoE();

            glPushMatrix();
                // Transforma a mão (último)
                glTranslatef(posicaoMaoX_E, posicaoMaoY_E, 0); // Translação da mão
                glRotatef(maoE, 0, 0, 1);             // Rotação da mão

                desenhaMaoE();
            glPopMatrix(); // Termina a transformação da mão

        glPopMatrix(); // Termina a transformação do antebraço



      glPopMatrix(); // Termina a transformação do braço

      glPushMatrix();
        glTranslatef(posicaoBracoX_D, posicaoBracoY_D, 0); // Define a posição inicial do braço direito
        glRotatef(bracoD, 0, 0, 1); // Rotaciona o braço direito
        desenhaBracoD();

        glPushMatrix();
            glTranslatef(posicaoAntebracoX_D, posicaoAntebracoY_D, 0); // Conecta o antebraço direito
            glRotatef(antebracoD, 0, 0, 1); // Rotaciona o antebraço direito
            desenhaAntebracoD();

            glPushMatrix();
                glTranslatef(posicaoMaoX_D, posicaoMaoY_D, 0); // Conecta a mão direita
                glRotatef(maoD, 0, 0, 1); // Rotaciona a mão direita
                desenhaMaoD();
            glPopMatrix();

        glPopMatrix();

      glPopMatrix();




      // Pernas (retângulos arredondados)
      glColor3f(0.0, 0.0, 1.0); // Cor das calças (azul)
      desenharRetanguloArredondado(-0.1, -0.05, 0.0, 0.2, 0.02); // Perna esquerda
      desenharRetanguloArredondado(0.0, -0.05, 0.1, 0.2, 0.02); // Perna direita

      // Ajuste na parte superior das calças
      glColor3f(1.0, 0.5, 0.5); // Cor da camiseta
      circulo(0.0, 0.25, 0.1005); // Círculo para cobrir o início das calças

      // Sandálias
      glColor3f(1.0, 0.5, 0.5); // Cor das sandálias
      desenharRetanguloArredondado(-0.07, -0.04, -0.03, -0.07, 0.01); // Sandália esquerda
      desenharRetanguloArredondado(0.03, -0.04, 0.07, -0.07, 0.01);  // Sandália direita

      // Estrela
      glColor3f(1.0, 1.0, 0.0); // Cor amarela para a estrela
      desenharEstrela(0.0, 0.36); // Desenha a estrela acima
  }

    glPopMatrix(); // Restaura o estado anterior da matriz de transformação
}

void animarFlores(){
  for(int i = 0; i < NUM_FLORES; i++){
      flores[i].x -= 0.1;

      if(flores[i].x < -1) flores[i].x = 100.0;

      flores[i].anguloRotacao += 0.5;
  }

  glutPostRedisplay(); // Redesenha a cena

}

void Animar(int interacoes) {
    animarFlores();  // Chama a função de animação
    glutTimerFunc(30, Animar, interacoes + 1);  // Chama a função novamente após 30ms
}
