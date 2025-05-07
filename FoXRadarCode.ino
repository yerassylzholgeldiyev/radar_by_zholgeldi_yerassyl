// Servo кітапханасын моторды басқару үшін қосамыз
#include <Servo.h>

// Ультрадыбыстық сенсор мен моторды басқаруға арналған тұрақты мәндерді анықтаймыз
#define ULTRASONIC_TRIG_PIN 10  // Ультрадыбыстық импульсті іске қосу үшін триггер пині
#define ULTRASONIC_ECHO_PIN 11  // Ультрадыбыстық импульстің қайтарылған сигналын алу пині
#define SERVO_PIN 12            // Серво мотор жалғанған пин

// Уақытты өлшеу және қашықтықты есептеу үшін айнымалыларды анықтаймыз
#define SOUND_SPEED 0.034       // Дыбыс жылдамдығы (см/мкс), 340 м/с

long timeInterval;              // Импульстің ұзақтығын сақтау үшін айнымалы
int measuredDistance;           // Есептелген қашықтықты сақтау үшін айнымалы

Servo motorControl;             // Серво моторды басқару үшін Servo объектісі

// Бастапқы орнату функциясы
void setup() {
  pinMode(ULTRASONIC_TRIG_PIN, OUTPUT); // Триггер пинін шығыс ретінде орнатамыз
  pinMode(ULTRASONIC_ECHO_PIN, INPUT);  // Эхо пинін кіріс ретінде орнатамыз
  Serial.begin(9600);                   // Сериялық байланысты бастаймыз
  motorControl.attach(SERVO_PIN);       // Серво моторды тиісті пинге қосамыз
}

// Негізгі цикл функциясы
void loop() {
  // Серво моторды 15-тен 165 градусқа дейін бұрып, қашықтықты өлшейміз
  for (int angle = 15; angle <= 165; angle++) {
    motorControl.write(angle);  // Сервоны ағымдағы бұрышқа бұрамыз
    delay(30);                  // Сервоның орнынан қозғалуы үшін кідіру
    measuredDistance = getDistance(); // Ультрадыбыстық сенсордан қашықтықты алу
    
    Serial.print(angle);        // Ағымдағы серво бұрышын шығарамыз
    Serial.print(",");          // Мәліметтерді бөлу үшін үтір қоямыз
    Serial.print(measuredDistance); // Өлшенген қашықтықты шығарамыз
    Serial.print(".");          // Мәліметтерді бөлу үшін нүкте қоямыз
  }

  // Серво моторды 165-тен 15 градусқа дейін кері бұрып, қайтадан өлшеу жасаймыз
  for (int angle = 165; angle > 15; angle--) {
    motorControl.write(angle);  // Сервоны ағымдағы бұрышқа кері бұрамыз
    delay(30);                  // Серво қозғалысы үшін кідіру
    measuredDistance = getDistance(); // Қайтадан қашықтықты өлшейміз
    
    Serial.print(angle);        // Сервоның кері қозғалыстағы бұрышын шығарамыз
    Serial.print(",");          // Мәліметтерді бөлу үшін үтір
    Serial.print(measuredDistance); // Өлшенген қашықтықты шығару
    Serial.print(".");          // Мәліметтерді бөлу үшін нүкте
  }
}

// Ультрадыбыстық сенсордан қашықтықты есептеу функциясы
int getDistance() {
  // Триггер пині арқылы импульсті бастау
  digitalWrite(ULTRASONIC_TRIG_PIN, LOW);  // Триггер пинін LOW күйіне түсіру
  delayMicroseconds(2);                    // Қысқа кідіріс, таза импульс үшін
  
  digitalWrite(ULTRASONIC_TRIG_PIN, HIGH); // Триггер пинін HIGH күйіне көтеру
  delayMicroseconds(10);                   // 10 микросекундтық импульс беру
  digitalWrite(ULTRASONIC_TRIG_PIN, LOW);  // Импульсті аяқтау (LOW күйіне қайтару)
  
  timeInterval = pulseIn(ULTRASONIC_ECHO_PIN, HIGH); // Қайтарылған импульстің уақытын өлшеу
  
  // Уақыт пен дыбыс жылдамдығына негізделіп қашықтықты есептеу (см түрінде)
  measuredDistance = timeInterval * SOUND_SPEED / 2;
  return measuredDistance;  // Есептелген қашықтық мәнін қайтарамыз
}
