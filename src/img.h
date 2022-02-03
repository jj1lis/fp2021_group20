#define WIDTH 300   // 映像の幅
#define HEIGHT 200  // 映像の高さ

// 色の構造体
// R, G, Bをそれぞれ0~255で指定
struct color{
    unsigned char r, g, b;
};

// 画像を真っ白にする (初期化)
void img_clear(void);

// 現在の画像をPPM型式で保存
// ファイル名は'imgdddd.ppm'で、出力するたびにdddd部分の数字が0001, 0002, 0003, ... と連番で増える
void img_write(void);

// 指定した位置(x, y)に色cの点を打つ
void img_putpixel(struct color c, int x, int y);

// 指定した位置(x, y)を中心とする半径rの円領域を色cで塗りつぶす
void img_fillcircle(struct color c, double x, double y, double r);

// 指定した位置(x, y)を中心とする幅w、高さhの矩形領域を色cで塗りつぶす
void img_fillrectangle(struct color c, int x, int y, int w, int h);
