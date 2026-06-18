/*
 * ============================================================
 *  ĐÈN GIAO THÔNG ESP32 + TM1637 + Web Control
 *  LED: Xanh (GPIO 25), Vàng (GPIO 26), Đỏ (GPIO 27)
 *  TM1637: CLK (GPIO 22), DIO (GPIO 21)
 *  Web Server: Port 80
 * ============================================================
 */

#include <WiFi.h>
#include <WebServer.h>
#include <TM1637Display.h>
#include <Preferences.h>

// ---- Cấu hình WiFi ----
const char* ssid     = "HOANG QUY";
const char* password = "quangquanquy";

// ---- Chân GPIO LED ----
#define LED_GREEN  25
#define LED_YELLOW 26
#define LED_RED    27

// ---- Chân TM1637 ----
#define CLK_PIN 22
#define DIO_PIN 21

// ---- Thời gian mặc định (giây) ----
#define DEFAULT_GREEN  30
#define DEFAULT_YELLOW  5
#define DEFAULT_RED    25

// ============================================================
//  Đối tượng toàn cục
// ============================================================
TM1637Display display(CLK_PIN, DIO_PIN);
WebServer      server(80);
Preferences    prefs;

// ---- Biến trạng thái ----
volatile int greenTime  = DEFAULT_GREEN;
volatile int yellowTime = DEFAULT_YELLOW;
volatile int redTime    = DEFAULT_RED;

enum Phase { PHASE_GREEN, PHASE_YELLOW, PHASE_RED };
volatile Phase currentPhase   = PHASE_GREEN;
volatile int   remainingTime  = DEFAULT_GREEN;
volatile bool  settingsChanged = false;

unsigned long lastTick = 0;   // mốc thời gian tick 1 giây

// ============================================================
//  HTML nhúng (Web UI)
// ============================================================
const char HTML_PAGE[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="vi">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Điều Khiển Đèn Giao Thông</title>
<style>
  @import url('https://fonts.googleapis.com/css2?family=Orbitron:wght@400;700;900&family=Rajdhani:wght@300;400;600&display=swap');

  :root {
    --green:  #00e676;
    --yellow: #ffea00;
    --red:    #ff1744;
    --bg:     #0a0a0f;
    --panel:  #12121a;
    --border: #1e1e2e;
    --text:   #e0e0f0;
    --muted:  #4a4a6a;
    --glow-g: 0 0 20px #00e67688, 0 0 40px #00e67644;
    --glow-y: 0 0 20px #ffea0088, 0 0 40px #ffea0044;
    --glow-r: 0 0 20px #ff174488, 0 0 40px #ff174444;
  }

  * { box-sizing: border-box; margin: 0; padding: 0; }

  body {
    background: var(--bg);
    color: var(--text);
    font-family: 'Rajdhani', sans-serif;
    min-height: 100vh;
    display: flex;
    flex-direction: column;
    align-items: center;
    padding: 20px;
    background-image:
      radial-gradient(ellipse at 20% 20%, #00e67611 0%, transparent 50%),
      radial-gradient(ellipse at 80% 80%, #ff174411 0%, transparent 50%);
  }

  h1 {
    font-family: 'Orbitron', sans-serif;
    font-weight: 900;
    font-size: clamp(1.2rem, 4vw, 2rem);
    letter-spacing: 4px;
    text-transform: uppercase;
    margin-bottom: 6px;
    background: linear-gradient(135deg, var(--green), var(--yellow), var(--red));
    -webkit-background-clip: text;
    -webkit-text-fill-color: transparent;
    background-clip: text;
  }

  .subtitle {
    color: var(--muted);
    font-size: 0.85rem;
    letter-spacing: 2px;
    margin-bottom: 30px;
    text-transform: uppercase;
  }

  .main-grid {
    display: grid;
    grid-template-columns: 1fr 2fr;
    gap: 20px;
    width: 100%;
    max-width: 900px;
  }

  @media (max-width: 600px) {
    .main-grid { grid-template-columns: 1fr; }
  }

  /* ---- Traffic Light Visual ---- */
  .traffic-box {
    background: var(--panel);
    border: 1px solid var(--border);
    border-radius: 20px;
    padding: 24px;
    display: flex;
    flex-direction: column;
    align-items: center;
    gap: 16px;
  }

  .traffic-pole {
    background: linear-gradient(180deg, #1e1e2e, #2a2a3e);
    border: 2px solid #2e2e4e;
    border-radius: 16px;
    padding: 20px 24px;
    display: flex;
    flex-direction: column;
    gap: 18px;
    box-shadow: inset 0 0 30px #00000066;
  }

  .led-circle {
    width: 70px;
    height: 70px;
    border-radius: 50%;
    transition: all 0.4s cubic-bezier(.25,.8,.25,1);
    position: relative;
    cursor: default;
  }

  .led-circle::after {
    content: '';
    position: absolute;
    top: 10px; left: 15px;
    width: 20px; height: 12px;
    background: rgba(255,255,255,0.25);
    border-radius: 50%;
    transform: rotate(-20deg);
  }

  .led-off {
    background: #1a1a2a;
    border: 2px solid #2a2a3a;
    box-shadow: none;
  }

  .led-green.active  { background: var(--green);  border: 2px solid #00ff88; box-shadow: var(--glow-g); }
  .led-yellow.active { background: var(--yellow); border: 2px solid #ffe000; box-shadow: var(--glow-y); }
  .led-red.active    { background: var(--red);    border: 2px solid #ff4466; box-shadow: var(--glow-r); }

  /* ---- 7-seg display ---- */
  .seg-display {
    font-family: 'Orbitron', monospace;
    font-size: 3.5rem;
    font-weight: 900;
    letter-spacing: 8px;
    padding: 12px 20px;
    border-radius: 10px;
    background: #060608;
    border: 2px solid #1a1a2e;
    min-width: 130px;
    text-align: center;
    transition: color 0.3s, text-shadow 0.3s;
  }

  .seg-green  { color: var(--green);  text-shadow: var(--glow-g); }
  .seg-yellow { color: var(--yellow); text-shadow: var(--glow-y); }
  .seg-red    { color: var(--red);    text-shadow: var(--glow-r); }

  .phase-label {
    font-family: 'Orbitron', sans-serif;
    font-size: 0.75rem;
    letter-spacing: 3px;
    text-transform: uppercase;
    color: var(--muted);
  }

  /* ---- Controls ---- */
  .controls-box {
    background: var(--panel);
    border: 1px solid var(--border);
    border-radius: 20px;
    padding: 28px;
    display: flex;
    flex-direction: column;
    gap: 22px;
  }

  .control-group {
    display: flex;
    flex-direction: column;
    gap: 10px;
  }

  .ctrl-header {
    display: flex;
    align-items: center;
    gap: 10px;
    margin-bottom: 4px;
  }

  .ctrl-dot {
    width: 12px; height: 12px;
    border-radius: 50%;
    flex-shrink: 0;
  }

  .ctrl-label {
    font-family: 'Orbitron', sans-serif;
    font-size: 0.75rem;
    letter-spacing: 2px;
    text-transform: uppercase;
  }

  .ctrl-row {
    display: flex;
    align-items: center;
    gap: 10px;
    background: #0d0d18;
    border: 1px solid var(--border);
    border-radius: 10px;
    padding: 10px 14px;
  }

  /* ---- Number Stepper ---- */
  .stepper {
    display: flex;
    align-items: center;
    gap: 0;
    flex: 1;
  }

  .step-btn {
    width: 36px; height: 38px;
    background: #1a1a2e;
    border: 1px solid var(--border);
    color: var(--text);
    font-size: 1.3rem;
    font-weight: 700;
    cursor: pointer;
    display: flex; align-items: center; justify-content: center;
    transition: background 0.15s;
    user-select: none;
    flex-shrink: 0;
  }
  .step-btn:first-child { border-radius: 8px 0 0 8px; }
  .step-btn:last-child  { border-radius: 0 8px 8px 0; }
  .step-btn:hover  { background: #2a2a44; }
  .step-btn:active { background: #3a3a5e; }

  .step-input {
    width: 64px;
    background: #0a0a14;
    border-top: 1px solid var(--border);
    border-bottom: 1px solid var(--border);
    border-left: none; border-right: none;
    color: var(--text);
    font-family: 'Orbitron', monospace;
    font-size: 1.1rem;
    font-weight: 700;
    padding: 6px 4px;
    text-align: center;
    outline: none;
    -moz-appearance: textfield;
  }
  .step-input::-webkit-outer-spin-button,
  .step-input::-webkit-inner-spin-button { -webkit-appearance: none; }
  .step-input:focus { background: #12122a; }

  input[type=number] {
    width: 60px;
    background: #0a0a14;
    border: 1px solid var(--border);
    border-radius: 6px;
    color: var(--text);
    font-family: 'Orbitron', monospace;
    font-size: 0.9rem;
    padding: 6px 8px;
    text-align: center;
    outline: none;
  }
  input[type=number]:focus { border-color: var(--muted); }

  .apply-btn {
    background: linear-gradient(135deg, #1e3a2e, #2a5a3e);
    border: 1px solid var(--green);
    color: var(--green);
    font-family: 'Orbitron', sans-serif;
    font-size: 0.8rem;
    font-weight: 700;
    letter-spacing: 3px;
    text-transform: uppercase;
    padding: 14px;
    border-radius: 10px;
    cursor: pointer;
    transition: all 0.2s;
    width: 100%;
  }
  .apply-btn:hover {
    background: linear-gradient(135deg, #2a5a3e, #3a7a4e);
    box-shadow: 0 0 20px #00e67644;
    transform: translateY(-1px);
  }
  .apply-btn:active { transform: translateY(0); }

  .toast {
    position: fixed;
    bottom: 30px;
    left: 50%;
    transform: translateX(-50%) translateY(80px);
    background: #1e2e1e;
    border: 1px solid var(--green);
    color: var(--green);
    font-family: 'Orbitron', sans-serif;
    font-size: 0.75rem;
    letter-spacing: 2px;
    padding: 12px 24px;
    border-radius: 8px;
    transition: transform 0.3s cubic-bezier(.25,.8,.25,1);
    z-index: 999;
    white-space: nowrap;
  }
  .toast.show { transform: translateX(-50%) translateY(0); }

  .status-bar {
    width: 100%;
    max-width: 900px;
    background: var(--panel);
    border: 1px solid var(--border);
    border-radius: 10px;
    padding: 10px 18px;
    display: flex;
    align-items: center;
    gap: 10px;
    font-size: 0.8rem;
    color: var(--muted);
    margin-top: 4px;
  }

  .status-dot {
    width: 8px; height: 8px;
    border-radius: 50%;
    background: var(--green);
    animation: pulse 1.5s infinite;
  }

  @keyframes pulse {
    0%,100% { opacity: 1; }
    50%      { opacity: 0.3; }
  }

  .divider {
    border: none;
    border-top: 1px solid var(--border);
  }
</style>
</head>
<body>

<h1>Đèn Giao Thông</h1>
<p class="subtitle">ESP32 Traffic Light Controller</p>

<div class="main-grid">

  <!-- Cột trái: đèn + số đếm -->
  <div class="traffic-box">
    <div class="traffic-pole">
      <div id="led-green"  class="led-circle led-green  led-off"></div>
      <div id="led-yellow" class="led-circle led-yellow led-off"></div>
      <div id="led-red"    class="led-circle led-red    led-off"></div>
    </div>
    <div id="seg" class="seg-display seg-green">--</div>
    <div id="phase-lbl" class="phase-label">Đang kết nối...</div>
  </div>

  <!-- Cột phải: điều khiển -->
  <div class="controls-box">
    <div class="control-group">
      <div class="ctrl-header">
        <div class="ctrl-dot" style="background:var(--green);box-shadow:var(--glow-g)"></div>
        <span class="ctrl-label" style="color:var(--green)">Đèn Xanh</span>
      </div>
      <div class="ctrl-row">
        <div class="stepper">
          <button class="step-btn" onclick="step('green',-1)">&#8722;</button>
          <input type="number" id="green-val" class="step-input" min="5" max="120" value="30">
          <button class="step-btn" onclick="step('green',1)">&#43;</button>
        </div>
        <span style="color:var(--muted);font-size:0.85rem;margin-left:6px">giây</span>
      </div>
    </div>

    <div class="control-group">
      <div class="ctrl-header">
        <div class="ctrl-dot" style="background:var(--yellow);box-shadow:var(--glow-y)"></div>
        <span class="ctrl-label" style="color:var(--yellow)">Đèn Vàng</span>
      </div>
      <div class="ctrl-row">
        <div class="stepper">
          <button class="step-btn" onclick="step('yellow',-1)">&#8722;</button>
          <input type="number" id="yellow-val" class="step-input" min="3" max="30" value="5">
          <button class="step-btn" onclick="step('yellow',1)">&#43;</button>
        </div>
        <span style="color:var(--muted);font-size:0.85rem;margin-left:6px">giây</span>
      </div>
    </div>

    <div class="control-group">
      <div class="ctrl-header">
        <div class="ctrl-dot" style="background:var(--red);box-shadow:var(--glow-r)"></div>
        <span class="ctrl-label" style="color:var(--red)">Đèn Đỏ</span>
      </div>
      <div class="ctrl-row">
        <div class="stepper">
          <button class="step-btn" onclick="step('red',-1)">&#8722;</button>
          <input type="number" id="red-val" class="step-input" min="5" max="120" value="25">
          <button class="step-btn" onclick="step('red',1)">&#43;</button>
        </div>
        <span style="color:var(--muted);font-size:0.85rem;margin-left:6px">giây</span>
      </div>
    </div>

    <hr class="divider">
    <button class="apply-btn" onclick="applySettings()">&#9654; Áp Dụng Cài Đặt</button>
  </div>
</div>

<div class="status-bar">
  <div class="status-dot"></div>
  <span id="status-txt">Đang cập nhật trạng thái...</span>
</div>

<div class="toast" id="toast">✓ ĐÃ LƯU CÀI ĐẶT</div>

<script>
  const PHASE_NAMES = { green: 'ĐÈN XANH', yellow: 'ĐÈN VÀNG', red: 'ĐỎ – DỪNG LẠI' };
  const SEG_CLASSES  = { green: 'seg-green', yellow: 'seg-yellow', red: 'seg-red' };
  const LIMITS = {
    green:  { min: 5,  max: 120 },
    yellow: { min: 3,  max: 30  },
    red:    { min: 5,  max: 120 }
  };

  // Theo dõi input nào đang được người dùng chỉnh
  const editing = { green: false, yellow: false, red: false };
  ['green','yellow','red'].forEach(c => {
    const el = document.getElementById(c+'-val');
    el.addEventListener('focus', () => editing[c] = true);
    el.addEventListener('blur',  () => editing[c] = false);
  });

  function step(color, delta) {
    const el  = document.getElementById(color+'-val');
    const lim = LIMITS[color];
    let v = parseInt(el.value) || lim.min;
    v = Math.min(lim.max, Math.max(lim.min, v + delta));
    el.value = v;
  }

  async function applySettings() {
    const g = parseInt(document.getElementById('green-val').value);
    const y = parseInt(document.getElementById('yellow-val').value);
    const r = parseInt(document.getElementById('red-val').value);
    // clamp trước khi gửi
    const gc = Math.min(120, Math.max(5,  g));
    const yc = Math.min(30,  Math.max(3,  y));
    const rc = Math.min(120, Math.max(5,  r));
    document.getElementById('green-val').value  = gc;
    document.getElementById('yellow-val').value = yc;
    document.getElementById('red-val').value    = rc;
    try {
      const res = await fetch(`/set?green=${gc}&yellow=${yc}&red=${rc}`);
      if (res.ok) showToast();
    } catch(e) { console.error(e); }
  }

  function showToast() {
    const t = document.getElementById('toast');
    t.classList.add('show');
    setTimeout(() => t.classList.remove('show'), 2500);
  }

  async function fetchStatus() {
    try {
      const res  = await fetch('/status');
      const data = await res.json();

      // LED
      ['green','yellow','red'].forEach(c => {
        document.getElementById('led-'+c).className =
          'led-circle led-' + c + (data.phase === c ? ' active' : ' led-off');
      });

      // Số đếm ngược
      const seg = document.getElementById('seg');
      seg.textContent = String(data.remaining).padStart(2,'0');
      seg.className   = 'seg-display ' + SEG_CLASSES[data.phase];

      // Nhãn pha
      document.getElementById('phase-lbl').textContent = PHASE_NAMES[data.phase] || '';

      // Chỉ cập nhật input nếu người dùng KHÔNG đang chỉnh
      ['green','yellow','red'].forEach(c => {
        if (!editing[c]) {
          const el = document.getElementById(c+'-val');
          if (parseInt(el.value) !== data[c+'Time']) {
            el.value = data[c+'Time'];
          }
        }
      });

      document.getElementById('status-txt').textContent =
        `Pha hiện tại: ${PHASE_NAMES[data.phase]} — Còn lại: ${data.remaining}s — IP: ${data.ip}`;
    } catch(e) {
      document.getElementById('status-txt').textContent = 'Mất kết nối với ESP32...';
    }
  }

  setInterval(fetchStatus, 800);
  fetchStatus();
</script>
</body>
</html>
)rawliteral";

// ============================================================
//  Web handlers
// ============================================================
void handleRoot() {
  server.send(200, "text/html", HTML_PAGE);
}

void handleSet() {
  if (server.hasArg("green"))  greenTime  = constrain(server.arg("green").toInt(),  5, 120);
  if (server.hasArg("yellow")) yellowTime = constrain(server.arg("yellow").toInt(), 3,  30);
  if (server.hasArg("red"))    redTime    = constrain(server.arg("red").toInt(),    5, 120);

  // Lưu flash
  prefs.begin("traffic", false);
  prefs.putInt("green",  greenTime);
  prefs.putInt("yellow", yellowTime);
  prefs.putInt("red",    redTime);
  prefs.end();

  settingsChanged = true;
  server.send(200, "text/plain", "OK");
  Serial.printf("[WEB] Cập nhật: G=%d Y=%d R=%d\n", greenTime, yellowTime, redTime);
}

void handleStatus() {
  const char* phaseStr;
  switch (currentPhase) {
    case PHASE_GREEN:  phaseStr = "green";  break;
    case PHASE_YELLOW: phaseStr = "yellow"; break;
    default:           phaseStr = "red";    break;
  }
  String json = "{";
  json += "\"phase\":\"" + String(phaseStr) + "\",";
  json += "\"remaining\":" + String(remainingTime) + ",";
  json += "\"greenTime\":"  + String(greenTime)  + ",";
  json += "\"yellowTime\":" + String(yellowTime) + ",";
  json += "\"redTime\":"    + String(redTime)    + ",";
  json += "\"ip\":\"" + WiFi.localIP().toString() + "\"";
  json += "}";
  server.send(200, "application/json", json);
}

// ============================================================
//  Hàm điều khiển đèn & màn hình
// ============================================================
void setLEDs(bool g, bool y, bool r) {
  digitalWrite(LED_GREEN,  g ? HIGH : LOW);
  digitalWrite(LED_YELLOW, y ? HIGH : LOW);
  digitalWrite(LED_RED,    r ? HIGH : LOW);
}

void showCountdown(int val) {
  if (val >= 100) {
    // Hiển thị 3 chữ số: tắt digit 0, bật digit 1-2-3
    int d2 = val / 100;
    int d1 = (val / 10) % 10;
    int d0 = val % 10;
    uint8_t segs[4] = {
      0x00,
      display.encodeDigit(d2),
      display.encodeDigit(d1),
      display.encodeDigit(d0)
    };
    display.setSegments(segs);
  } else {
    // Hiển thị 2 chữ số ở 2 digit cuối, 2 digit đầu tắt
    int d1 = val / 10;
    int d0 = val % 10;
    uint8_t segs[4] = {
      0x00,
      0x00,
      display.encodeDigit(d1),
      display.encodeDigit(d0)
    };
    display.setSegments(segs);
  }
}

// ============================================================
//  Chuyển pha
// ============================================================
void goToPhase(Phase p) {
  currentPhase = p;
  switch (p) {
    case PHASE_GREEN:
      remainingTime = greenTime;
      setLEDs(true, false, false);
      break;
    case PHASE_YELLOW:
      remainingTime = yellowTime;
      setLEDs(false, true, false);
      break;
    case PHASE_RED:
      remainingTime = redTime;
      setLEDs(false, false, true);
      break;
  }
  showCountdown(remainingTime);
  Serial.printf("[PHASE] %s — %d giây\n",
    p==PHASE_GREEN?"XANH":(p==PHASE_YELLOW?"VÀNG":"ĐỎ"), remainingTime);
}

// ============================================================
//  Setup
// ============================================================
void setup() {
  Serial.begin(115200);

  // Đọc cài đặt từ flash
  prefs.begin("traffic", true);
  greenTime  = prefs.getInt("green",  DEFAULT_GREEN);
  yellowTime = prefs.getInt("yellow", DEFAULT_YELLOW);
  redTime    = prefs.getInt("red",    DEFAULT_RED);
  prefs.end();

  // GPIO
  pinMode(LED_GREEN,  OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED,    OUTPUT);
  setLEDs(false, false, false);

  // TM1637
  display.setBrightness(7);
  display.showNumberDec(0, true);

  // WiFi
  Serial.printf("\nKết nối WiFi: %s\n", ssid);
  WiFi.begin(ssid, password);
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 30) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.printf("\nIP: %s\n", WiFi.localIP().toString().c_str());
  } else {
    Serial.println("\nKhông kết nối được WiFi! Chạy ngoại tuyến.");
  }

  // Web routes
  server.on("/",       handleRoot);
  server.on("/set",    handleSet);
  server.on("/status", handleStatus);
  server.begin();
  Serial.println("[WEB] Server started");

  // Bắt đầu với đèn xanh
  goToPhase(PHASE_GREEN);
  lastTick = millis();
}

// ============================================================
//  Loop
// ============================================================
void loop() {
  server.handleClient();

  unsigned long now = millis();

  // Tick mỗi 1 giây
  if (now - lastTick >= 1000) {
    lastTick = now;

    // Nếu cài đặt vừa thay đổi và đang ở cuối chu kỳ hiện tại
    // → áp dụng ngay từ đầu chu kỳ tiếp theo
    // (không cắt ngang giữa chừng)

    remainingTime--;
    showCountdown(max(0, (int)remainingTime));
    Serial.printf("[TICK] %s còn %d giây\n",
      currentPhase==PHASE_GREEN?"XANH":(currentPhase==PHASE_YELLOW?"VÀNG":"ĐỎ"),
      remainingTime);

    if (remainingTime <= 0) {
      // Chuyển pha theo thứ tự: XANH → VÀNG → ĐỎ → XANH
      switch (currentPhase) {
        case PHASE_GREEN:  goToPhase(PHASE_YELLOW); break;
        case PHASE_YELLOW: goToPhase(PHASE_RED);    break;
        case PHASE_RED:    goToPhase(PHASE_GREEN);  break;
      }
    }
  }
}
