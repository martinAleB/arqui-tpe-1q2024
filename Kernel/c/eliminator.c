#include <videoDriver.h>
#include <stdint.h>

#define RED 0x00FF0000
#define GREEN 0x0000FF00
#define BLUE 0x000000FF
#define BLACK 0
#define PLAYER1_COLOR BLUE
#define PLAYER2_COLOR GREEN
#define PIXEL_SIZE 4
#define OFFSET_FROM_CORNER 40
#define WIDTH (256-2*OFFSET_FROM_CORNER)
#define HEIGHT (192-2*OFFSET_FROM_CORNER)
#define START_X_OFFSET (WIDTH/8)
#define START_Y_OFFSET (WIDTH/8)

unsigned char playground[WIDTH][HEIGHT];

typedef struct {
    uint8_t x;
    uint8_t y;
    uint8_t lost;
    uint32_t color;
} Player;

void putLargePixel(uint32_t color, uint8_t x, uint8_t y, uint8_t n){
    drawRectangle (color, n*(x+OFFSET_FROM_CORNER), n*(y+OFFSET_FROM_CORNER), n*(x+OFFSET_FROM_CORNER+1),n*(y+OFFSET_FROM_CORNER+1));
}

unsigned char isOccupied(uint8_t x, uint8_t y){
    return playground[x][y];
}

void move(Player *p, uint8_t x, uint8_t y){
    putLargePixel(p->color, p->x+=x, p->y+=y, PIXEL_SIZE);
    if (isOccupied(p->x,p->y)) p->lost=1; else playground[p->x][p->y]=1;
    
}

void initPlayground(){
    drawRectangle (RED, PIXEL_SIZE*(OFFSET_FROM_CORNER), PIXEL_SIZE*(OFFSET_FROM_CORNER), PIXEL_SIZE * (WIDTH+OFFSET_FROM_CORNER),PIXEL_SIZE*(HEIGHT+OFFSET_FROM_CORNER));
    drawRectangle (BLACK, PIXEL_SIZE*(OFFSET_FROM_CORNER+1), PIXEL_SIZE*(OFFSET_FROM_CORNER+1), PIXEL_SIZE * (WIDTH+OFFSET_FROM_CORNER-1),PIXEL_SIZE*(HEIGHT+OFFSET_FROM_CORNER-1));
    for (int i=0; i < WIDTH;i++){playground[i][0]=1;playground[i][HEIGHT-1]=1;}
    for (int i=0; i < HEIGHT;i++){playground[0][i]=1;playground[WIDTH-1][i]=1;}
}

void ai(unsigned char * playground[], Player *p){
    while (!p->lost && !isOccupied(p->x,p->y))move(p,1,0);
    //while (1) if (!playground[p->x][p->y]) move(p, 1, 0); else break;
    while (!p->lost)move(p,0,-1);
}

void eliminator(){
    //PREGUNTAR VELOCIDAD Y TAMANO Y JUGADORES ANTES DE INICIALIZAR
    initPlayground();
    Player p1 = {1,START_Y_OFFSET, 0, PLAYER1_COLOR};
    //Player p2 = {START_X_OFFSET,HEIGHT-START_Y_OFFSET, 0, PLAYER2_COLOR};
    Player p2 = {WIDTH-START_X_OFFSET,HEIGHT-START_Y_OFFSET, 0, PLAYER2_COLOR};
    //while (!p1.lost) move (&p1, 0, -1);
    //while (!p2.lost) move (&p2, 1, 1);
    ai(playground,&p2);
    while (1);
}

