#define DUST_LED_PIN 13   //LED핀 미세먼지센서에 Digital에 연결한다.
#define DUST_DATA_PIN 35  //데이터핀 미세먼지센서에 Analog에 연결한다.
int voValue[16];          //미세먼지 값을 저장할 배열 변수
float Correction = 0.06;  //미세먼지 값을 보정할 보정변수
float Sensitivity = 0.33; //미세먼지 값의 정확도를 높여줄 센서변수
long sumValue;            //미세먼지 값의 필터에 사용될 함수
void setup()
{
  Serial.begin(9600);
  pinMode(DUST_LED_PIN, OUTPUT);
}

void loop()
{
  /*
   * 미세먼지의 값을 16번 읽어와 voValue[] 배열에 대입한다.
   */
  for(int i=0; i<16; i++){
    digitalWrite(DUST_LED_PIN, LOW);
    delayMicroseconds(280);
    voValue[i] = analogRead(DUST_DATA_PIN);
    if(voValue[i]<50) i--; // 노이즈 필터 : 50보다 작은 값은 노이즈로 인식하고 다시 값을 읽는다.
    delayMicroseconds(40);
    digitalWrite(DUST_LED_PIN, HIGH);
    delayMicroseconds(9620);
  }
  /*
   * 거품정렬
   * voValue배열의 값을 낮은 값에서 높은 값으로 정리한다.
   */
  for(int i=0; i<16; i++){
    for(int j=1; j<16-i; j++){
      if(voValue[j-1]>voValue[j]){
        int temp = voValue[j];
        voValue[j] = voValue[j-1];
        voValue[j-1] = temp;
      }
    }
  }
  /*
   * 정렬된 값에서 낮은 값 4개 높은 값 4개를 제외한 
   * 나머지 값을 모두 더한다. 
   * 너무 높거나 너무 낮은 값은 노이즈일 
   * 가능성이 높기 때문에 제외한다.
   */
  for(int i=4; i<12; i++){
    sumValue=sumValue+voValue[i];
  } 
  /*
   * 시프트연산자
   * 주어진 값을 시프트한다. 
   * 0010 0010(34)  >>  0001 0001(17)
   * 0010 0010(34)  <<  0100 0100(68)
   * >>를 이용해 나눗샘이 가능하다.
   * >>1은 나누기 2와 같다. >>2는 나누기 4와 같다.
   * >>3은 나누기 8과 같다.
   * 나누기 대신 시프트연산자를 사용하면 처리속도가 빨라진다.
   * 위 sumValue에 저장된 값은 voValue[4]~[11] 8개다.
   * 8로 나누어 평균값을 구한다.
   */
  sumValue = sumValue>>3;

  /*
   * ESP32에서 사용되는 전압 3.3을 ADC분해능 12bit값인 4096으로
   * 나누어 ADC값 1당 적용되는 전압을 구해 calcVoltage에 대입한다.
   * calcVoltage에서 보정값을 빼고 센서값을 나누어 100을 곱한다.
   * 
   * 데이터시트에서는 0.5V당 100ug/m3이지만 이는 5V전압을 사용한 경우이다.
   * ESP32는 3.3V를 사용하기 때문에 비례된 값을 0.33V당 100ug/m3를 맞추어
   * 계산한다.
   * 
   * 단 아날로그 센서의 값은 센서마다 다르므로 정확한 측정을 위해서는 기준을
   * 만들고 그에 따라 센서값과 보정값을 조정해야 한다.
   */
  float calcVoltage = sumValue * (3.3 / 4096);
  float dustDensity = (calcVoltage - Correction)/Sensitivity*100;
  
  Serial.print("dust : ");
  Serial.print(dustDensity);
  Serial.println("ug/m3");
  Serial.print("ADC voltage : ");
  Serial.print(calcVoltage);
  Serial.println("V");
  sumValue = 0; //초기화
  delay(1000);
}
