/*
 * Hiển thị bảng chữ cái A-Z trên module MAX7219 LED Matrix 8x8
 * Thay đổi chữ cái dựa trên khoảng cách đo từ cảm biến siêu âm HC-SR04.
 * Sử dụng thư viện LedControl
 * 
 * Kết nối MAX7219:
 *   DIN -> Pin 13
 *   CS  -> Pin 12
 *   CLK -> Pin 11
 *   VCC -> 5V
 *   GND -> GND
 *
 * Kết nối HC-SR04:
 *   TRIG -> Pin 9
 *   ECHO -> Pin 10
 *   VCC  -> 5V
 *   GND  -> GND
 */

#include "LedControl.h"

// Thiết lập các chân LED ma trận
#define DIN 13
#define CS  12
#define CLK 11

// Thiết lập các chân cảm biến siêu âm (HC-SR04)
#define TRIG_PIN 9
#define ECHO_PIN 10

// Tạo đối tượng điều khiển (1 module)
LedControl matrix = LedControl(DIN, CLK, CS, 1);

// ========== BẢNG CHỮ CÁI A - Z (font 5x7 trên ma trận 8x8) ==========
// Mỗi chữ cái được mã hoá thành 8 byte (8 hàng)

const byte chu_A[8] = {0x18, 0x24, 0x42, 0x42, 0x7E, 0x42, 0x42, 0x00};
const byte chu_B[8] = {0x7C, 0x42, 0x42, 0x7C, 0x42, 0x42, 0x7C, 0x00};
const byte chu_C[8] = {0x3C, 0x42, 0x40, 0x40, 0x40, 0x42, 0x3C, 0x00};
const byte chu_D[8] = {0x78, 0x44, 0x42, 0x42, 0x42, 0x44, 0x78, 0x00};
const byte chu_E[8] = {0x7E, 0x40, 0x40, 0x7C, 0x40, 0x40, 0x7E, 0x00};
const byte chu_F[8] = {0x7E, 0x40, 0x40, 0x7C, 0x40, 0x40, 0x40, 0x00};
const byte chu_G[8] = {0x3C, 0x42, 0x40, 0x4E, 0x42, 0x42, 0x3C, 0x00};
const byte chu_H[8] = {0x42, 0x42, 0x42, 0x7E, 0x42, 0x42, 0x42, 0x00};
const byte chu_I[8] = {0x3E, 0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00};
const byte chu_J[8] = {0x1E, 0x04, 0x04, 0x04, 0x04, 0x44, 0x38, 0x00};
const byte chu_K[8] = {0x42, 0x44, 0x48, 0x70, 0x48, 0x44, 0x42, 0x00};
const byte chu_L[8] = {0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x7E, 0x00};
const byte chu_M[8] = {0x42, 0x66, 0x5A, 0x42, 0x42, 0x42, 0x42, 0x00};
const byte chu_N[8] = {0x42, 0x62, 0x52, 0x4A, 0x46, 0x42, 0x42, 0x00};
const byte chu_O[8] = {0x3C, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00};
const byte chu_P[8] = {0x7C, 0x42, 0x42, 0x7C, 0x40, 0x40, 0x40, 0x00};
const byte chu_Q[8] = {0x3C, 0x42, 0x42, 0x42, 0x4A, 0x44, 0x3A, 0x00};
const byte chu_R[8] = {0x7C, 0x42, 0x42, 0x7C, 0x48, 0x44, 0x42, 0x00};
const byte chu_S[8] = {0x3C, 0x42, 0x40, 0x3C, 0x02, 0x42, 0x3C, 0x00};
const byte chu_T[8] = {0x7F, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00};
const byte chu_U[8] = {0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00};
const byte chu_V[8] = {0x42, 0x42, 0x42, 0x42, 0x24, 0x24, 0x18, 0x00};
const byte chu_W[8] = {0x42, 0x42, 0x42, 0x42, 0x5A, 0x66, 0x42, 0x00};
const byte chu_X[8] = {0x42, 0x24, 0x18, 0x18, 0x18, 0x24, 0x42, 0x00};
const byte chu_Y[8] = {0x41, 0x22, 0x14, 0x08, 0x08, 0x08, 0x08, 0x00};
const byte chu_Z[8] = {0x7E, 0x02, 0x04, 0x18, 0x20, 0x40, 0x7E, 0x00};

// Mảng con trỏ tới tất cả chữ cái để dễ duyệt
const byte* bangChuCai[26] = {
  chu_A, chu_B, chu_C, chu_D, chu_E, chu_F, chu_G,
  chu_H, chu_I, chu_J, chu_K, chu_L, chu_M, chu_N,
  chu_O, chu_P, chu_Q, chu_R, chu_S, chu_T, chu_U,
  chu_V, chu_W, chu_X, chu_Y, chu_Z
};

// Thời gian hiển thị mỗi chữ cái (ms)
#define THOI_GIAN_HIEN_THI 1000

// Hàm hiển thị 1 ký tự lên ma trận
void hienThiKyTu(const byte* kyTu) {
  for (int hang = 0; hang < 8; hang++) {
    matrix.setRow(0, hang, kyTu[hang]);
  }
}

// Hiệu ứng chuyển tiếp: xoá từ trên xuống
void hieuUngXoa() {
  for (int hang = 0; hang < 8; hang++) {
    matrix.setRow(0, hang, 0x00);
    delay(30);
  }
}

void setup() {
  // Tắt chế độ ngủ cho module 0
  matrix.shutdown(0, false);
  // Chỉnh độ sáng (0 - 15)
  matrix.setIntensity(0, 5);
  // Xoá màn hình
  matrix.clearDisplay(0);

  // Cấu hình chân cảm biến siêu âm
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  // Phát xung trigger
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Đọc thời gian echo
  long duration = pulseIn(ECHO_PIN, HIGH);
  
  // Tính khoảng cách (cm)
  int distance = duration * 0.034 / 2;

  // Kiểm tra khoảng cách và hiển thị chữ cái tương ứng
  // Code viết dài bằng các lệnh if cơ bản để dễ hiểu nhất
  if (distance < 4) {
    hienThiKyTu(chu_A);
  } else if (distance < 6) {
    hienThiKyTu(chu_B);
  } else if (distance < 8) {
    hienThiKyTu(chu_C);
  } else if (distance < 10) {
    hienThiKyTu(chu_D);
  } else if (distance < 12) {
    hienThiKyTu(chu_E);
  } else if (distance < 14) {
    hienThiKyTu(chu_F);
  } else if (distance < 16) {
    hienThiKyTu(chu_G);
  } else if (distance < 18) {
    hienThiKyTu(chu_H);
  } else if (distance < 20) {
    hienThiKyTu(chu_I);
  } else if (distance < 22) {
    hienThiKyTu(chu_J);
  } else if (distance < 24) {
    hienThiKyTu(chu_K);
  } else if (distance < 26) {
    hienThiKyTu(chu_L);
  } else if (distance < 28) {
    hienThiKyTu(chu_M);
  } else if (distance < 30) {
    hienThiKyTu(chu_N);
  } else if (distance < 32) {
    hienThiKyTu(chu_O);
  } else if (distance < 34) {
    hienThiKyTu(chu_P);
  } else if (distance < 36) {
    hienThiKyTu(chu_Q);
  } else if (distance < 38) {
    hienThiKyTu(chu_R);
  } else if (distance < 40) {
    hienThiKyTu(chu_S);
  } else if (distance < 42) {
    hienThiKyTu(chu_T);
  } else if (distance < 44) {
    hienThiKyTu(chu_U);
  } else if (distance < 46) {
    hienThiKyTu(chu_V);
  } else if (distance < 48) {
    hienThiKyTu(chu_W);
  } else if (distance < 50) {
    hienThiKyTu(chu_X);
  } else if (distance < 52) {
    hienThiKyTu(chu_Y);
  } else {
    hienThiKyTu(chu_Z);
  }

  // Trễ một chút để cảm biến siêu âm hoạt động ổn định
  delay(100);
}
