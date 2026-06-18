#include <Arduino.h>
#include <IRremote.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <Servo.h>

DFRobotDFPlayerMini mp3;
SoftwareSerial chan_du_lieu(5, 6);  // RX, TX

int chan_tin_hieu = 3;

IRrecv remote(chan_tin_hieu);
decode_results ket_qua;

// Chân điều khiển
int chan_den_do = 10;   // Đèn LED Đỏ (PWM)
int chan_den_xanh = 9;  // Đèn LED Xanh Blue (PWM)
int chan_servo = 11;    // Chân điều khiển Servo

Servo myServo;

// Khai báo các chế độ
enum CheDo {
  CHE_DO_DEN,
  CHE_DO_NHAC,
  CHE_DO_QUAT
};

CheDo cheDoHienTai = CHE_DO_NHAC;  // Bắt đầu ở chế độ nhạc mặc định

// Biến trạng thái
int doSangDo = 0;
int doSangXanh = 0;
bool trangThaiDen = false;
bool trangThaiServo = false;
int gocServo = 0;

// CÁC MÃ PHÍM HỒNG NGOẠI (Dạng số thập phân)
// Cần xem Serial Monitor để cập nhật lại đúng mã remote của bạn
#define PHIM_1 16753245  // Phím 1: Chế độ ĐÈN
#define PHIM_2 16736925  // Phím 2: Chế độ NHẠC
#define PHIM_3 16769565  // Phím 3: Chế độ QUẠT (Dùng Servo)
#define M_TEN_LEN 16718055
#define M_TEN_XUONG 16730805
#define M_TEN_TRAI 16716015
#define M_TEN_PHAI 16734885
#define PHIM_SAO 16726215    // Phím *
#define PHIM_THANG 16756815  // Phím #

void setup() {
  Serial.begin(9600);
  chan_du_lieu.begin(9600);

  // Khởi tạo chân Đèn và Servo
  pinMode(chan_den_do, OUTPUT);
  pinMode(chan_den_xanh, OUTPUT);
  myServo.attach(chan_servo);
  myServo.write(0);

  analogWrite(chan_den_do, 0);
  analogWrite(chan_den_xanh, 0);

  if (mp3.begin(chan_du_lieu)) {
    Serial.println("DFPlayer OK");
  } else {
    Serial.println("Loi ket noi voi DFPlayer Mini");
  }

  mp3.setTimeOut(500);
  mp3.volume(20);  // Đặt âm lượng ban đầu (0-30)

  remote.enableIRIn();
}

void loop() {
  if (remote.decode(&ket_qua)) {
    unsigned long gia_tri = ket_qua.value;

    // Bỏ qua mã lặp (thường là 0x0)
    if (gia_tri != 0) {
      Serial.print("Ma IR: ");
      Serial.println(gia_tri);

      switch (gia_tri) {
        case PHIM_1:
          cheDoHienTai = CHE_DO_DEN;
          Serial.println("=> CHUYỂN SANG: ĐIỀU KHIỂN ĐÈN");
          break;

        case PHIM_2:
          cheDoHienTai = CHE_DO_NHAC;
          Serial.println("=> CHUYỂN SANG: PHÁT NHẠC");
          break;

        case PHIM_3:
          cheDoHienTai = CHE_DO_QUAT;
          Serial.println("=> CHUYỂN SANG: ĐIỀU KHIỂN QUẠT (SERVO)");
          break;

        case M_TEN_LEN:
          if (cheDoHienTai == CHE_DO_DEN) {
            if (trangThaiDen) {
              doSangDo += 25;
              if (doSangDo > 255) doSangDo = 255;
              analogWrite(chan_den_do, doSangDo);
              Serial.print("Đèn Đỏ: Tăng -> ");
              Serial.println(doSangDo);
            }
          } else if (cheDoHienTai == CHE_DO_NHAC) {
            mp3.volumeUp();
            Serial.println("Nhạc: Tăng âm lượng");
          } else if (cheDoHienTai == CHE_DO_QUAT) {
            if (trangThaiServo) {
              gocServo += 15;
              if (gocServo > 180) gocServo = 180;
              myServo.write(gocServo);
              Serial.print("Quạt (Servo): Tăng góc -> ");
              Serial.println(gocServo);
            }
          }
          break;

        case M_TEN_XUONG:
          if (cheDoHienTai == CHE_DO_DEN) {
            if (trangThaiDen) {
              doSangDo -= 25;
              if (doSangDo < 0) doSangDo = 0;
              analogWrite(chan_den_do, doSangDo);
              Serial.print("Đèn Đỏ: Giảm -> ");
              Serial.println(doSangDo);
            }
          } else if (cheDoHienTai == CHE_DO_NHAC) {
            mp3.volumeDown();
            Serial.println("Nhạc: Giảm âm lượng");
          } else if (cheDoHienTai == CHE_DO_QUAT) {
            if (trangThaiServo) {
              gocServo -= 15;
              if (gocServo < 0) gocServo = 0;
              myServo.write(gocServo);
              Serial.print("Quạt (Servo): Giảm góc -> ");
              Serial.println(gocServo);
            }
          }
          break;

        case M_TEN_TRAI:
          if (cheDoHienTai == CHE_DO_DEN) {
            if (trangThaiDen) {
              doSangXanh -= 25;
              if (doSangXanh < 0) doSangXanh = 0;
              analogWrite(chan_den_xanh, doSangXanh);
              Serial.print("Đèn Xanh Blue: Giảm -> ");
              Serial.println(doSangXanh);
            }
          } else if (cheDoHienTai == CHE_DO_NHAC) {
            mp3.previous();
            Serial.println("Nhạc: Bài trước");
          } else if (cheDoHienTai == CHE_DO_QUAT) {
            if (trangThaiServo) {
              gocServo = 0;
              myServo.write(gocServo);
              Serial.println("Quạt (Servo): Quay về 0 độ");
            }
          }
          break;

        case M_TEN_PHAI:
          if (cheDoHienTai == CHE_DO_DEN) {
            if (trangThaiDen) {
              doSangXanh += 25;
              if (doSangXanh > 255) doSangXanh = 255;
              analogWrite(chan_den_xanh, doSangXanh);
              Serial.print("Đèn Xanh Blue: Tăng -> ");
              Serial.println(doSangXanh);
            }
          } else if (cheDoHienTai == CHE_DO_NHAC) {
            mp3.next();
            Serial.println("Nhạc: Bài tiếp theo");
          } else if (cheDoHienTai == CHE_DO_QUAT) {
            if (trangThaiServo) {
              gocServo = 180;
              myServo.write(gocServo);
              Serial.println("Quạt (Servo): Quay đến 180 độ");
            }
          }
          break;

        case PHIM_SAO:
        case PHIM_THANG:
          if (cheDoHienTai == CHE_DO_DEN) {
            // Bất kỳ phím * hay # nào cũng bật/tắt đèn
            trangThaiDen = !trangThaiDen;
            if (trangThaiDen) {
              if (doSangDo == 0 && doSangXanh == 0) {
                doSangDo = 150;
                doSangXanh = 150;
              }
              analogWrite(chan_den_do, doSangDo);
              analogWrite(chan_den_xanh, doSangXanh);
              Serial.println("Đèn: BẬT");
            } else {
              analogWrite(chan_den_do, 0);
              analogWrite(chan_den_xanh, 0);
              Serial.println("Đèn: TẮT");
            }
          } else if (cheDoHienTai == CHE_DO_NHAC) {
            if (gia_tri == PHIM_SAO) {
              mp3.pause();
              Serial.println("Nhạc: Tạm dừng (Pause)");
            } else if (gia_tri == PHIM_THANG) {
              mp3.start();
              Serial.println("Nhạc: Tiếp tục phát (Play)");
            }
          } else if (cheDoHienTai == CHE_DO_QUAT) {
            trangThaiServo = !trangThaiServo;
            if (trangThaiServo) {
              if (gocServo == 0) gocServo = 90;
              myServo.write(gocServo);
              Serial.println("Quạt (Servo): BẬT");
            } else {
              myServo.write(0);
              Serial.println("Quạt (Servo): TẮT");
            }
          }
          break;
      }
    }
    remote.resume();
    delay(100);
  }
}