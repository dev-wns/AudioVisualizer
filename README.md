## 미리보기

<p align="center">
  <img src="https://postfiles.pstatic.net/MjAyMDA4MDNfMjQ0/MDAxNTk2NDA0Njk4MzUz.wDCxv_0FhLWwdTqlknG6rcx2b1xAB3kT5PWQHAJVl8og.65SPWMH1Mx4Ba8UIHs0Ck-Fv-q77Ot4LAiGqGXPGNUog.GIF.ashi0/ezgif-4-5e0391c06286.gif?type=w966">

## 동영상 주소

[Youtube] : https://www.youtube.com/watch?v=c654-wR1OR8
<br><br/>

## 개발 SDK

* DirectX11

* FModEx
<br><br/>

## 단축키
|단축키|     내용     |
|:---:|:--------:|
|**Space**|음악재생|
|**F1**|백그라운드 이미지 켜기/끄기|
|**F2**|센터 이미지 켜기/끄기|
|**F3**|센터 이미지 크기 감소|
|**F4**|센터 이미지 크기 증가|
|**F5**|스펙트럼 크기 감소|
|**F6**|스펙트럼 크기 증가|
|**F7**|베이스 파워 감소|
|**F8**|베이스 파워 증가|

## 적용 기술

### 인스턴싱
</p> <div align="center"> < 사진 > </div>
</p> <div align="center"> < 인스턴싱 > </div>
  파티클과 스펙트럼의 바(사각형) 부분은 같은 오브젝트지만 위치, 크기, 회전량, 색상 정도만 다르기 때문에 <br>
  인스턴싱으로 렌더링 해보자 라는 생각을 했습니다. <br>
  
### 안티앨리어싱
</p> <div align="center"> < 사진 > </div>
</p> <div align="center"> < 안티앨리어싱 > </div>
  사각형을 기울여서 렌더링 했을 때 테두리가 계단현상 때문에 부자연스러웠습니다. <br>
  관련 내용을 찾아보다가 DirectX에 안티 앨리어싱이라는 기술이 있는 것을 보고 <br>
  MSAA x8(multi sampling anti-aliasing)을 적용하여 계단현상을 해결해봤습니다. <br>

### 240 fps 고정
</p> <div align="center"> < 사진 > </div>
</p> <div align="center"> < 240 fps 고정 > </div>
  오브젝트에 관련된 렌더링 부분은 240 fps로 고정 했습니다.<br>
  제한을 걸지 않고 실행하면 GPU 점유율이 90% 이상 나와서 제한을 걸어야 겠다는 생각을 했습니다.<br>

## 프로그램에 대한 기술 설명

### 스펙트럼

* 좌우에서 들리는 사운드에 대한 스펙트럼 값을 더한 후 2로 나누어 평균 값을 사용했습니다. <br>

* 센터 이미지는 스펙트럼의 특정 값에 따라 변하도록 효과를 주었습니다. <br>

* 스펙트럼 바의 개수는 왼쪽 90개, 대칭으로 오른쪽 90개 총 180개 입니다.<br>

### 파티클

* 파티클 개수는 128개 입니다.<br>

* 스펙트럼 바와 마찬가지로 스펙트럼의 특정 부분 값에 따라 파티클의 속도에 변화를 주었습니다.<br>
