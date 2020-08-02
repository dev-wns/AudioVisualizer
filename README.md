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

## 적용 기술

### 인스턴싱
</p> <div align="center"> < 인스턴싱 > </div>
  파티클과 스펙트럼의 바(사각형) 부분은 같은 오브젝트지만 위치, 크기, 회전량, 색상 정도만 다르기 때문에 <br>
  인스턴싱으로 렌더링 해보자 라는 생각을 했습니다. <br>
  
### 안티앨리어싱
</p> <div align="center"> < 안티앨리어싱 > </div>
  사각형을 기울여서 렌더링 했을 때 테두리가 계단현상 때문에 부자연스러웠습니다. <br>
  조금 찾아보다가 DirectX에 안티 앨리어싱이라는 기술이 있는 것을 보고 <br>
  MSAA x4(multi sampling anti-aliasing)를 적용하여 계단현상을 해결해봤습니다. br>

### 240 fps 고정
</p> <div align="center"> < 240 fps 고정 > </div>
  정확하게는 렌더링 부분을 240 fps로 고정 했습니다.<br>
  제한을 걸지 않고 실행하면 GPU 점유율이 90% 이상 나와서 제한을 걸어야 겠다는 생각을 했습니다.<br>
  240 fps로 고정하면 제 컴퓨터 사양 기준으로 GPU 9% 정도의 점유율이 나옵니다.<br>
