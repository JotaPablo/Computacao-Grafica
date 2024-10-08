#include <GL/glut.h> //O arquivo glut.h inclui, além dos protótipos das funções GLUT, os arquivos gl.h e glu.h,
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define TRUE 1
#define FALSE 0
#define PI 3.14159265358979323846

void circulo(float x, float y, float raio);
void semiCirculo(float x, float y, float raio, int voltadoParaCima);
void desenhaMontanhas();
void desenhaNuvens();
void desenhaVegetacao();
void desenhaAlvo();
void drawStevePizza(float x, float y, float scale);
void display(void);
void desenharSteven(float scale, float translateX, float translateY);


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

  // Desenha o Céu
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

  // Desenha nuvens
  desenhaNuvens();

  // Desenha o sol
  glColor3ub(253, 255, 231); // Cor amarela
  circulo(65.0, 45.0, 4.5); // Círculo central

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

    glColor3ub(85, 194, 249); // Cor Escura
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

  //Desenha Vegetação
  desenhaVegetacao();

   //Desenha Steve Pizza
  drawStevePizza(20, 25, 10);

  //Desenha Steven
  desenharSteven(15, 80, 40);

 
  
  

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

//Função para fazer um semi circulo
  //TRUE para o semi circulo voltado para cima e FALSE para baixo
void semiCirculo(float x, float y, float raio, int voltadoParaCima) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Centro do semicírculo

    if (voltadoParaCima) {
        // Desenha o semicírculo voltado para cima (de 0 a PI)
        for (int i = 0; i <= 50; i++) {
            float angulo = PI * i / 50; 
            glVertex2f(x + (raio * cosf(angulo)), y + (raio * sinf(angulo)));
        }
    } else {
        // Desenha o semicírculo voltado para baixo (de PI a 2PI)
        for (int i = 50; i <= 100; i++) {
            float angulo = 2.0 * PI * i / 100; 
            glVertex2f(x + (raio * cosf(angulo)), y + (raio * sinf(angulo)));
        }
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




void desenhaNuvens(){

  //Listras no ceú
    glBegin(GL_TRIANGLES);
      glColor3ub(176, 225, 255);
      glVertex2f(0, 60);   
      glVertex2f(5, 60);  
      glVertex2f(0, 45);

      
      glVertex2f(100, 60);   
      glVertex2f(100, 45);  
      glVertex2f(85, 60);
     
      glVertex2f(55, 60);   
      glVertex2f(56, 60);  
      glVertex2f(52, 50);

      glVertex2f(23, 60);   
      glVertex2f(26, 60);  
      glVertex2f(19, 50);
      
    
    glEnd();

  //Nuvem 1
    glColor3ub(210, 231, 236);
      semiCirculo(9.8, 53.5, 2.5, FALSE);
      semiCirculo(15.2, 53.5, 2.5, FALSE);
    
    glColor3ub(255, 255, 255);
      semiCirculo(10, 52.5, 2.5, TRUE);
      semiCirculo(15, 52.5, 2.5, TRUE);
  
    //base quadrada de sombra
    
    glBegin(GL_QUADS);
      //parte de baixo um tom de cinza
      glColor3ub(210, 231, 236);
      glVertex2f(10.0, 51);   // Ponto inferior esquerdo
      glVertex2f(15, 51);  // Ponto inferior direito
      glVertex2f(15, 53.5); // Ponto superior direito
      glVertex2f(10, 53.5);  // Ponto superior esquerdo

      //parte de cima branca
      glColor3ub(255, 255, 255);
      glVertex2f(10.0, 52.5);   // Ponto inferior esquerdo
      glVertex2f(15, 52.5);  // Ponto inferior direito
      glVertex2f(15, 55); // Ponto superior direito
      glVertex2f(10, 55);  // Ponto superior esquerdO
      
    glEnd();

  //Nuvem 2
    glColor3ub(255, 255, 255);
      semiCirculo(30, 50, 6, TRUE);
      semiCirculo(40, 50, 8, TRUE);
    
  //Nuvem 3
    glColor3ub(254, 254, 253);
      semiCirculo(4, 44, 4, TRUE);
      semiCirculo(9, 43, 3, TRUE);
  
  //Nuvem 4
    glColor3ub(255, 255, 255);
      semiCirculo(48.6, 35.2, 2.5, TRUE);
      semiCirculo(43, 34.5, 5, TRUE);
  
  //Nuvem 5(em baixo do Sol)
    glColor3ub(255, 255, 255);
      semiCirculo(63, 35, 2, TRUE);
      semiCirculo(67, 35, 3, TRUE);

  //Nuvem 6
    glColor3ub(255, 255, 255);
      semiCirculo(85, 47, 7, TRUE);
      semiCirculo(93, 49, 7, TRUE);

  //Mini nuvens
    glColor3ub(255, 255, 255);
      circulo(3, 59, 0.4);
      circulo(1, 57, 0.4);

      semiCirculo(20, 45.7, 0.4, TRUE);
      semiCirculo(22, 46, 0.6, TRUE);

      //semiCirculo(54, 44, 0.6, TRUE);
      //semiCirculo(53, 44, 0.8, TRUE);

      semiCirculo(74, 55, 0.6, TRUE);
      semiCirculo(75, 55, 0.8, TRUE);
      semiCirculo(76, 55, 0.6, TRUE);


      //semiCirculo(61, 53, 0.8, TRUE);
      //semiCirculo(62, 53, 0.6, TRUE);

            
      semiCirculo(50, 56, 0.7, TRUE);

      semiCirculo(90, 57, 0.7, TRUE);
      circulo(98, 56, 0.5);

      semiCirculo(40, 46, 0.7, TRUE);

}

void desenhaGrama(float x, float y){
    semiCirculo(x, y, 1.5, TRUE);
    semiCirculo(x - 1.5, y, 1, TRUE);
    semiCirculo(x + 1.5, y, 0.8, TRUE);
}

void desenhaFlor(float x, float y){
  
  //Rosa mais claro pra petola
  glColor3ub(243, 154, 181);
  //Superior
    circulo(x, y + 0.7, 0.7);
  //Inferior
  circulo(x, y - 0.7, 0.7);

  //Esquerdo
  circulo(x-0.7, y, 0.7);
  //Direita
  circulo(x+0.7, y, 0.7); 

  //Meio
  glColor3ub(237, 86, 155); //Rosa mais escuro para o meio da flor
  circulo(x, y, 0.3);
}


void desenhaFlorVirada(float x, float y){

  //Rosa para petolas
  glColor3ub(242, 137, 155);


  //Superior esquerdo
  circulo(x-0.5, y + 0.5, 0.7);
  //Superior direito
  circulo(x+0.5, y + 0.5, 0.7);

  //Inferior esquerdo
  circulo(x-0.5, y - 0.5, 0.7);
  //Infferior direito
  circulo(x+0.5, y - 0.5, 0.7); 

  //Meio
  glColor3ub(237, 86, 155); //Rosa mais escuro para o meio da flor
  circulo(x, y, 0.3);
}

void desenhaVegetacao(){

  //Matinhos na montanha esquerda
  glColor3ub(155, 181, 147);
  desenhaGrama(5, 33);
  desenhaGrama(9, 37);
  desenhaGrama(15, 31);

  //desenhaGrama(11.2,42);
  //desenhaGrama(24,36.5);
  
  //Matinhos na montanha direita
  glColor3ub(155, 181, 147);
  desenhaGrama(78, 35);
  desenhaGrama(90, 39);
  desenhaGrama(85, 43);

  //Matinhos montanha do meio
  glColor3ub(155, 181, 147);
  desenhaGrama(49, 30);
  desenhaGrama(38, 30);
  desenhaGrama(32, 36);

  //Flores na montanha direita
  desenhaFlor(90, 43);
  desenhaFlorVirada(85, 32);
  desenhaFlorVirada(72, 34);
  desenhaFlorVirada(80, 40);

  //Flores na montanha do meio
  desenhaFlor(45,34);
  desenhaFlor(54,32);

  desenhaFlorVirada(30,40);
  desenhaFlorVirada(37,35);

  //Flores na montanha da esquerda
  desenhaFlor(10, 32);
  desenhaFlor(21, 33);
  desenhaFlor(3, 38);
  desenhaFlor(15, 36);

  desenhaFlorVirada(5,43.5);
  desenhaFlorVirada(18,40);
  desenhaFlorVirada(29,33);
}


void drawCircle(float cx, float cy, float r, int num_segments);



// Função para desenhar um retângulo arredondado (com círculos nas bordas)
void drawRoundedRect(float x1, float y1, float x2, float y2, float radius) {
    // Ajuste o raio para garantir que ele não ultrapasse o tamanho do retângulo
    float rectWidth = x2 - x1;
    float rectHeight = y2 - y1;

    // Limita o raio para não ser maior que metade da largura ou altura do retângulo
    if (radius > rectWidth / 2) radius = rectWidth / 2;
    if (radius > rectHeight / 2) radius = rectHeight / 2;

    // Desenhar o retângulo central sem as bordas arredondadas
    glBegin(GL_QUADS);
    glVertex2f(x1 + radius, y1);
    glVertex2f(x2 - radius, y1);
    glVertex2f(x2 - radius, y2);
    glVertex2f(x1 + radius, y2);
    glEnd();

    // Desenhar os círculos nas bordas para arredondar
    drawCircle(x1 + radius, y1 + radius, radius, 50);
    drawCircle(x2 - radius, y1 + radius, radius, 50);
    drawCircle(x1 + radius, y2 - radius, radius, 50);
    drawCircle(x2 - radius, y2 - radius, radius, 50);

    // Desenhar os retângulos nas laterais para completar o arredondamento
    glBegin(GL_QUADS);
    glVertex2f(x1, y1 + radius);
    glVertex2f(x1 + radius, y1 + radius);
    glVertex2f(x1 + radius, y2 - radius);
    glVertex2f(x1, y2 - radius);

    glVertex2f(x2 - radius, y1 + radius);
    glVertex2f(x2, y1 + radius);
    glVertex2f(x2, y2 - radius);
    glVertex2f(x2 - radius, y2 - radius);
    glEnd();
}




// Função para desenhar um retângulo
void drawRect(float x1, float y1, float x2, float y2) {
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}

// Função para desenhar um círculo
void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy); // Centro do círculo
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * M_PI * i / num_segments;
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

// Função para desenhar uma estrela
void drawStar(float offsetX, float offsetY) {
    glBegin(GL_TRIANGLE_FAN);

    // Cor da estrela (amarelo)
    glColor3f(1.0, 1.0, 0.0);

    // Definindo o centro da estrela
    glVertex2f(offsetX, offsetY); // Centro da estrela em (offsetX, offsetY)

    // Vértices da estrela
    for (int i = 0; i <= 10; i++) {
        // Cálculo do ângulo
        float angle = i * 2 * M_PI / 10; // 10 vértices (5 pontas)
        
        // Raio da estrela
        float radius = (i % 2 == 0) ? 0.07 : 0.02; // Raio maior 0.1, menor 0.03

        // Calculando as coordenadas x e y
        float x = radius * cos(angle) + offsetX; // Adiciona offsetX
        float y = radius * sin(angle) + offsetY; // Adiciona offsetY
        
        glVertex2f(x, y); // Adiciona o vértice calculado
    }

    glEnd();
}

void desenharSteven(float scale, float translateX, float translateY){

    // Aplicando translação e escala
    glPushMatrix(); // Salva o estado atual da matriz de transformação
    glTranslatef(translateX, translateY, 0.0); // Movimenta o personagem
    glScalef(scale, scale, 1.0); // Aplica a escala


    // Corpo (retângulo arredondado)
    glColor3f(1.0, 0.5, 0.5); // Cor rosada para a camiseta
    drawRoundedRect(-0.1, 0.1, 0.1, 0.5, 0.05); // Corpo com bordas arredondadas
    
    

     // Círculos de transição manga-corpo
    glColor3f(1.0, 0.5, 0.5); // Rosa para os círculos
    drawCircle(-0.085, 0.46, 0.05, 50); // Circulo de transição esquerdo
    drawCircle(0.085, 0.46, 0.05, 50); // Circulo de transição direito

    glColor3f(0.0, 0.0, 0.0); // Cor do cabelo
    drawCircle(-0.08, 0.62, 0.08, 50); // Mecha esquerda
    drawCircle(0.08, 0.62, 0.08, 50);  // Mecha espelhada no lado direito
    

    // Cabeça (círculo)
    glColor3f(1.0, 0.8, 0.6); // Cor da pele
    drawCircle(0.0, 0.6, 0.12, 50); // Cabeça



    // Orelha 
    glColor3f(1.0, 0.8, 0.6); // Cor da pele para a orelha
    drawCircle(-0.12, 0.62, 0.03, 50); // Orelha esquerda
    drawCircle(0.12, 0.62, 0.03, 50); // Orelha direita


    // Cabelo (círculos)
    glColor3f(0.0, 0.0, 0.0); // Cor do cabelo
    drawCircle(0.0, 0.74, 0.08, 50);
    drawCircle(0.0, 0.78, 0.08, 50); // Círculo central
    drawCircle(-0.07, 0.75, 0.07, 50); // Círculo esquerdo
    drawCircle(0.07, 0.75, 0.07, 50); // Círculo direito
    drawCircle(-0.1, 0.69, 0.06, 50); // Círculo mais para a esquerda
    drawCircle(0.1, 0.69, 0.06, 50); // Círculo mais para a direita
    drawCircle(-0.11, 0.67, 0.05, 50);
    drawCircle(0.11, 0.67, 0.05, 50);

    // Sobrancelhas
    glColor3f(0.0, 0.0, 0.0);
    semiCirculo(0.05, 0.625, 0.025, 1);
    semiCirculo(-0.05, 0.625, 0.025, 1);

    // Olhos (ajuste a coordenada y)
    glColor3f(1.0, 1.0, 1.0); // Branco
    drawCircle(-0.05, 0.58, 0.035, 50); // Olho esquerdo (y ajustado)
    drawCircle(0.05, 0.58, 0.035, 50);  // Olho direito (y ajustado)

    // Pupilas (ajuste a coordenada y)
    glColor3f(0.0, 0.0, 0.0); // Preto
    drawCircle(-0.06, 0.56, 0.013, 50); // Pupila esquerda (y ajustado)
    drawCircle(0.035, 0.56, 0.013, 50);  // Pupila direita (y ajustado)

    // Contorno superior do sorriso (semicírculo)
    glColor3f(0.0, 0.0, 0.0); // Cor da linha do contorno da boca
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 100; i++) {
        float theta = M_PI * i / 100; // Ângulo para desenhar o semicírculo
        float x = 0.05 * cos(theta);  // Raio maior no eixo x para o sorriso
        float y = 0.03 * sin(theta);  // Raio menor no eixo y (para a largura da boca)
        glVertex2f(x, 0.52 - y);      // Ajusta a posição vertical da boca
    }
    glEnd();

    // Parte interna da boca (preenchimento)
    glColor3f(0.5, 0.0, 0.0); // Cor preta para a parte interna da boca
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0, 0.51);  // Centro do preenchimento da boca
    for (int i = 0; i <= 100; i++) {
        float theta = M_PI * i / 100; // Ângulo para desenhar o semicírculo
        float x = 0.05 * cos(theta);  // Raio maior no eixo x para o preenchimento
        float y = 0.03 * sin(theta);  // Raio menor no eixo y
        glVertex2f(x, 0.51 - y);      // Ajusta a posição vertical da boca preenchida
    }
    glEnd();

    // Dentes 
    glColor3f(1.0, 1.0, 1.0); // Branco para os dentes
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0, 0.52);  // Centro dos dentes
    for (int i = 0; i <= 100; i++) {
        float theta = M_PI * i / 100; // Ângulo para desenhar o semicírculo
        float x = 0.04 * cos(theta);  // Raio para os dentes
        float y = 0.02 * sin(theta);  // Ajuste a altura dos dentes
        glVertex2f(x, 0.52 - y);      // Posiciona os dentes
    }
    glEnd();


    // Braços (retângulos arredondados)
    glColor3f(1.0, 0.8, 0.6); // Cor da pele
    drawRoundedRect(-0.18, 0.2, -0.1, 0.5, 0.02); // Braço esquerdo
    drawRoundedRect(0.1, 0.2, 0.18, 0.5, 0.02);  // Braço direito

    // Mangas (ajuste a posição e tamanho)
    glColor3f(1.0, 0.5, 0.5); // Cor rosada da manga
    drawRoundedRect(-0.19, 0.4, -0.08, 0.5, 0.02); // Manga esquerda arredondada
    drawRoundedRect(0.08, 0.4, 0.19, 0.5, 0.02);   // Manga direita arredondada

    
    // Pernas (retângulos arredondados)
    glColor3f(0.0, 0.0, 1.0); // Cor da calça
    drawRoundedRect(-0.1, -0.05, 0.0, 0.2, 0.02); // Perna esquerda arredondada
    drawRoundedRect(0.0, -0.05, 0.1, 0.2, 0.02); // Perna direita arredondada

    // Ajuste na roupinha
    glColor3f(1.0, 0.5, 0.5); // Mesma cor do corpo (camiseta)
    drawCircle(0.0, 0.25, 0.1005, 50); // Círculo posicionado para cobrir o início das calças 

    // Sandálias 
 
    glColor3f(1.0, 0.5, 0.5); // Cor das sandálias
    drawRoundedRect(-0.07, -0.04, -0.03, -0.07, 0.01); // Sandália esquerda
    drawRoundedRect(0.03, -0.04, 0.07, -0.07, 0.01);  // Sandália direita

    // Estrela  
    drawStar(0.0,0.4); 

    
}

void drawStevePizza(float x, float y, float scale) {
    // Fatia de pizza (triângulo com a base para cima)
    
    // Borda alaranjada (casca da pizza)
    glColor3f(1.0, 0.5, 0.0); // Cor alaranjada da borda
    glBegin(GL_TRIANGLES);
    glVertex2f(x - 0.2 * scale, y + 0.4 * scale);  // Ponto esquerdo da base
    glVertex2f(x + 0.0 * scale, y + 0.4 * scale);  // Ponto direito da base
    glVertex2f(x + 0.0 * scale, y - 0.4 * scale);  // Ponto inferior (ponta da pizza)
    glEnd();

    // Parte interna da pizza (amarela)
    glColor3f(1.0, 0.9, 0.3); // Cor amarela da pizza
    glBegin(GL_TRIANGLES);
    glVertex2f(x - 0.18 * scale, y + 0.38 * scale);  // Ponto esquerdo da base (um pouco menor que a borda)
    glVertex2f(x + 0.18 * scale, y + 0.38 * scale);  // Ponto direito da base
    glVertex2f(x + 0.0 * scale, y - 0.35 * scale);   // Ponto inferior (ponta da pizza, também menor)
    glEnd();

    // Borda recheada na parte de cima da pizza
    glColor3f(1.0, 0.7, 0.2); // Cor da borda recheada (uma tonalidade mais clara)
    glBegin(GL_QUADS);
    glVertex2f(x - 0.2 * scale, y + 0.35 * scale);   // Ponto inferior esquerdo da borda recheada
    glVertex2f(x + 0.19 * scale, y + 0.35 * scale);  // Ponto inferior direito da borda recheada
    glVertex2f(x + 0.14 * scale, y + 0.45 * scale);  // Ponto superior direito da borda recheada
    glVertex2f(x - 0.25 * scale, y + 0.45 * scale);  // Ponto superior esquerdo da borda recheada
    glEnd();

    // Oculos escuros - lente esquerda
    glColor3f(0.0, 0.0, 0.0); // Cor dos óculos (preto)
    glBegin(GL_QUADS);
    glVertex2f(x - 0.1 * scale, y + 0.15 * scale);  // Ponto inferior esquerdo do óculo esquerdo
    glVertex2f(x + 0.01 * scale, y + 0.15 * scale); // Ponto inferior direito do óculo direito
    glVertex2f(x + 0.01 * scale, y + 0.10 * scale); // Ponto superior direito do óculo direito
    glVertex2f(x - 0.1 * scale, y + 0.10 * scale);  // Ponto superior esquerdo do óculo esquerdo
    glEnd();

    // Oculos escuros - lente direita
    float offsetX = 0.15 * scale;
    glBegin(GL_QUADS);
    glVertex2f(x - 0.1 * scale + offsetX, y + 0.15 * scale);  // Ponto inferior esquerdo
    glVertex2f(x + 0.01 * scale + offsetX, y + 0.15 * scale); // Ponto inferior direito
    glVertex2f(x + 0.01 * scale + offsetX, y + 0.10 * scale); // Ponto superior direito
    glVertex2f(x - 0.1 * scale + offsetX, y + 0.10 * scale);  // Ponto superior esquerdo
    glEnd();

    // Lentes dos óculos
    glColor3f(0.0, 0.0, 0.0);
    semiCirculo(x - 0.04 * scale, y + 0.15 * scale, 0.08 * scale, 0);
    semiCirculo(x + 0.1 * scale, y + 0.15 * scale, 0.08 * scale, 0);

    // Desenha um retângulo para a perna do óculos
    glColor3f(0.0, 0.0, 0.0); // Cor da perna (preto)
    glBegin(GL_QUADS);
    glVertex2f(x - 0.15 * scale, y + 0.13 * scale);  // Ponto inferior esquerdo da perna
    glVertex2f(x - 0.1 * scale, y + 0.13 * scale);   // Ponto inferior direito da perna
    glVertex2f(x - 0.1 * scale, y + 0.11 * scale);   // Ponto superior direito da perna
    glVertex2f(x - 0.15 * scale, y + 0.11 * scale);  // Ponto superior esquerdo da perna
    glEnd();

    // Contorno superior do sorriso (semicírculo)
    glColor3f(0.0, 0.0, 0.0); // Cor da linha do contorno da boca
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 100; i++) {
        float theta = PI * i / 100;  // Ângulo para desenhar o semicírculo
        float smileX = 0.05 * scale * cos(theta); // Raio maior no eixo x para o sorriso
        float smileY = 0.03 * scale * sin(theta); // Raio menor no eixo y (para a largura da boca)
        glVertex2f(x + smileX, y - smileY);  // Ajusta a posição vertical da boca para baixo
    }
    glEnd();

    // Parte interna da boca (preenchimento)
    glColor3f(0.0, 0.0, 0.0); // Cor vermelha escura para a parte interna da boca
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Centro do preenchimento da boca
    for (int i = 0; i <= 100; i++) {
        float theta = PI * i / 100;  // Ângulo para desenhar o semicírculo
        float fillX = 0.05 * scale * cos(theta); // Raio maior no eixo x para o preenchimento
        float fillY = 0.03 * scale * sin(theta); // Raio menor no eixo y
        glVertex2f(x + fillX, y - fillY);  // Ajusta a posição vertical da boca preenchida
    }
    glEnd();

    // Língua (semicírculo menor dentro da boca)
    glColor3f(1.0, 0.0, 0.0); // Cor da língua (vermelho vivo)
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y - 0.01 * scale); // Centro da língua
    for (int i = 0; i <= 100; i++) {
        float theta = PI * i / 100;  // Ângulo para desenhar o semicírculo da língua
        float tongueX = 0.03 * scale * cos(theta); // Raio menor para a língua
        float tongueY = 0.015 * scale * sin(theta); // Altura da língua
        glVertex2f(x + tongueX, y - 0.01 * scale - tongueY); // Ajuste da posição vertical para colocar dentro da boca
    }
    glEnd();
}




  
