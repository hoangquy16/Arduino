#include <Arduino.h>
#include <LedControl.h>

//Thiết lập chân cho MAX7219
#define DIN_PIN 12
#define CS_PIN 11
#define CLK_PIN 10

//Tạo biến chọn thời gian hiển thị giữa các biểu tượng (đơn vị: ms)
#define DISPLAY_DELAY 10
#define CHUYENCHUCAI 500
//Tạo đối tượng LedControl
//Số lượng thiết bị MAX7219 được sử dụng là 1, nếu bạn sử dụng nhiều hơn thì thay đổi số này cho phù hợp
LedControl matrix = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 1);

//Tạo các biểu tượng bằng mã HEX
//Sử dụng công cụ chuyển đổi Pixel to HEX để tạo mã HEX cho các biểu tượng bạn muốn hiển thị
// ========== BẢNG CHỮ CÁI A - Z (font 5x7 trên ma trận 8x8) ==========
// Mỗi chữ cái được mã hoá thành 8 byte (8 hàng)
const byte A[8] = {0x18, 0x24, 0x42, 0x42, 0x7E, 0x42, 0x42, 0x00};
const byte B[8] = {0x7C, 0x42, 0x42, 0x7C, 0x42, 0x42, 0x7C, 0x00};
const byte C[8] = {0x3C, 0x42, 0x40, 0x40, 0x40, 0x42, 0x3C, 0x00};
const byte D[8] = {0x78, 0x44, 0x42, 0x42, 0x42, 0x44, 0x78, 0x00};
const byte E[8] = {0x7E, 0x40, 0x40, 0x7C, 0x40, 0x40, 0x7E, 0x00};
const byte F[8] = {0x7E, 0x40, 0x40, 0x7C, 0x40, 0x40, 0x40, 0x00};
const byte G[8] = {0x3C, 0x42, 0x40, 0x4E, 0x42, 0x42, 0x3C, 0x00};
const byte H[8] = {0x42, 0x42, 0x42, 0x7E, 0x42, 0x42, 0x42, 0x00};
const byte I[8] = {0x3E, 0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00};
const byte J[8] = {0x1E, 0x04, 0x04, 0x04, 0x04, 0x44, 0x38, 0x00};
const byte K[8] = {0x42, 0x44, 0x48, 0x70, 0x48, 0x44, 0x42, 0x00};
const byte L[8] = {0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x7E, 0x00};
const byte M[8] = {0x42, 0x66, 0x5A, 0x42, 0x42, 0x42, 0x42, 0x00};
const byte N[8] = {0x42, 0x62, 0x52, 0x4A, 0x46, 0x42, 0x42, 0x00};
const byte O[8] = {0x3C, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00};
const byte P[8] = {0x7C, 0x42, 0x42, 0x7C, 0x40, 0x40, 0x40, 0x00};
const byte Q[8] = {0x3C, 0x42, 0x42, 0x42, 0x4A, 0x44, 0x3A, 0x00};
const byte R[8] = {0x7C, 0x42, 0x42, 0x7C, 0x48, 0x44, 0x42, 0x00};
const byte S[8] = {0x3C, 0x42, 0x40, 0x3C, 0x02, 0x42, 0x3C, 0x00};
const byte T[8] = {0x7F, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00};
const byte U[8] = {0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00};
const byte V[8] = {0x42, 0x42, 0x42, 0x42, 0x24, 0x24, 0x18, 0x00};
const byte W[8] = {0x42, 0x42, 0x42, 0x42, 0x5A, 0x66, 0x42, 0x00};
const byte X[8] = {0x42, 0x24, 0x18, 0x18, 0x18, 0x24, 0x42, 0x00};
const byte Y[8] = {0x41, 0x22, 0x14, 0x08, 0x08, 0x08, 0x08, 0x00};
const byte Z[8] = {0x7E, 0x02, 0x04, 0x18, 0x20, 0x40, 0x7E, 0x00};

void setup() {
  //Khởi động MAX7219
  matrix.shutdown(0, false); // Bật thiết bị
  matrix.setIntensity(0, 8); // Đặt độ sáng (0-15)
  matrix.clearDisplay(0); // Xóa màn hình
}
void loop() {
  //Hiển thị chữ bảng chữ cái
  for (int i = 0; i < 8; i++){
    matrix.setRow(0, i, A[i]); // Hiển thị chữ A
    delay(DISPLAY_DELAY); // Đợi 200ms
    }
  delay(CHUYENCHUCAI);
  for (int i = 0; i < 8; i++){
    matrix.setRow(0, i, B[i]); // Hiển thị chữ B
    delay(DISPLAY_DELAY); // Đợi 200ms
    }
  delay(CHUYENCHUCAI);
  for (int i = 0; i < 8; i++){
    matrix.setRow(0, i, C[i]); // Hiển thị chữ C
    delay(DISPLAY_DELAY); // Đợi 200ms
    }
  delay(CHUYENCHUCAI);
  for (int i = 0; i < 8; i++){
    matrix.setRow(0, i, D[i]); // Hiển thị chữ D
    delay(DISPLAY_DELAY); // Đợi 200ms
    }
  delay(CHUYENCHUCAI);
  for (int i = 0; i < 8; i++){
    matrix.setRow(0, i, E[i]); // Hiển thị chữ E
    delay(DISPLAY_DELAY); // Đợi 200ms  
    }
  delay(CHUYENCHUCAI);
  for (int i = 0; i < 8; i++){
    matrix.setRow(0, i, F[i]); // Hiển thị chữ F
    delay(DISPLAY_DELAY); // Đợi 200ms
    }
  delay(CHUYENCHUCAI);
  for (int i = 0; i < 8; i++){
    matrix.setRow(0, i, G[i]); // Hiển thị chữ G
    delay(DISPLAY_DELAY); // Đợi 200ms
    }
  delay(CHUYENCHUCAI);
  for (int i = 0; i < 8; i++){
    matrix.setRow(0, i, H[i]); // Hiển thị chữ H
    delay(DISPLAY_DELAY); // Đợi 200ms
    }
  delay(CHUYENCHUCAI);
  for (int i = 0; i < 8; i++){
    matrix.setRow(0, i, I[i]); // Hiển thị chữ I
    delay(DISPLAY_DELAY); // Đợi 200ms
    }
  delay(CHUYENCHUCAI);
  for (int i = 0; i < 8; i++){
    matrix.setRow(0, i, J[i]); // Hiển thị chữ J
    delay(DISPLAY_DELAY); // Đợi 200ms
    }
  delay(CHUYENCHUCAI);
  for (int i = 0; i < 8; i++){
    matrix.setRow(0, i, K[i]); // Hiển thị chữ K
    delay(DISPLAY_DELAY); // Đợi 200ms
    }
  delay(CHUYENCHUCAI);
  for (int i = 0; i < 8; i++){
    matrix.setRow(0, i, L[i]); // Hiển thị chữ L
    delay(DISPLAY_DELAY); // Đợi 200ms
    }
  delay(CHUYENCHUCAI);
  for (int i = 0; i < 8; i++){
    matrix.setRow(0, i, M[i]); // Hiển thị chữ M
    delay(DISPLAY_DELAY); // Đợi 200ms
    }
  delay(CHUYENCHUCAI);
  for (int i = 0; i < 8; i++){
    matrix.setRow(0, i, N[i]); // Hiển thị chữ N
    delay(DISPLAY_DELAY); // Đợi 200ms
    }
  delay(CHUYENCHUCAI);
  for (int i = 0; i < 8; i++){
    matrix.setRow(0, i, O[i]); // Hiển thị chữ O
    delay(DISPLAY_DELAY); // Đợi 200ms
    }
  delay(CHUYENCHUCAI);
  for (int i = 0; i < 8; i++){
    matrix.setRow(0, i, P[i]); // Hiển thị chữ P
    delay(DISPLAY_DELAY); // Đợi 200ms
    }
  delay(CHUYENCHUCAI);
  for (int i = 0; i < 8; i++){
    matrix.setRow(0, i, Q[i]); // Hiển thị chữ Q
    delay(DISPLAY_DELAY); // Đợi 200ms
    }
  delay(CHUYENCHUCAI);
  for (int i = 0; i < 8; i++){
    matrix.setRow(0, i, R[i]); // Hiển thị chữ R
    delay(DISPLAY_DELAY); // Đợi 200ms
    }
  delay(CHUYENCHUCAI);
  for (int i = 0; i < 8; i++){
    matrix.setRow(0, i, S[i]); // Hiển thị chữ S
    delay(DISPLAY_DELAY); // Đợi 200ms
    }
  delay(CHUYENCHUCAI);
  for (int i = 0; i < 8; i++){
    matrix.setRow(0, i, T[i]); // Hiển thị chữ T
    delay(DISPLAY_DELAY); // Đợi 200ms
    }
  delay(CHUYENCHUCAI);
  for (int i = 0; i < 8; i++){
    matrix.setRow(0, i, U[i]); // Hiển thị chữ U
    delay(DISPLAY_DELAY); // Đợi 200ms
    }
  delay(CHUYENCHUCAI);
  for (int i = 0; i < 8; i++){
    matrix.setRow(0, i, V[i]); // Hiển thị chữ V
    delay(DISPLAY_DELAY); // Đợi 200ms
    }
  delay(CHUYENCHUCAI);
  for (int i = 0; i < 8; i++){
    matrix.setRow(0, i, W[i]); // Hiển thị chữ W
    delay(DISPLAY_DELAY); // Đợi 200ms
    }
  delay(CHUYENCHUCAI);
  for (int i = 0; i < 8; i++){
    matrix.setRow(0, i, X[i]); // Hiển thị chữ X
    delay(DISPLAY_DELAY); // Đợi 200ms
    }
  delay(CHUYENCHUCAI);
  for (int i = 0; i < 8; i++){
    matrix.setRow(0, i, Y[i]); // Hiển thị chữ Y
    delay(DISPLAY_DELAY); // Đợi 200ms
    }
  delay(CHUYENCHUCAI);
  for (int i = 0; i < 8; i++){
    matrix.setRow(0, i, Z[i]); // Hiển thị chữ Z
    delay(DISPLAY_DELAY); // Đợi 200ms
    }
}
 