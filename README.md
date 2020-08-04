## 미리보기

<p align="center">
  <img src="https://postfiles.pstatic.net/MjAyMDA4MDNfMjQ0/MDAxNTk2NDA0Njk4MzUz.wDCxv_0FhLWwdTqlknG6rcx2b1xAB3kT5PWQHAJVl8og.65SPWMH1Mx4Ba8UIHs0Ck-Fv-q77Ot4LAiGqGXPGNUog.GIF.ashi0/ezgif-4-5e0391c06286.gif?type=w966">

[Youtube] : https://www.youtube.com/watch?v=c654-wR1OR8 <br>

## 설명

오디오 파일을 읽은 후 해당 오디오의 스펙트럼 값을 시각화 하여 보여주는 프로그램 입니다. <br>
Steam Wallpaper Engine 중 사용자가 만든 Audio Visualizer 바탕화면에서 영감을 얻어 제작했습니다. <br>

## 단축키
|  단축키  |     내용                | 단축키  |         내용         |
|:-------:|:-----------------------:|:-------:|:-------------------:|
|**Space**|음악재생                  |**ESC**  |프로그램 종료         |
|**F1**   |백그라운드 이미지 끄기/켜기 |**F2**   |센터 이미지 끄기/켜기 |     
|**F3**   |센터 이미지 크기 감소      |**F4**   |센터 이미지 크기 증가  |      
|**F5**   |스펙트럼 크기 감소         |**F6**   |스펙트럼 크기 증가    |
|**F7**   |베이스 파워 감소           |**F8**   |베이스 파워 증가      |
|**-**   |볼륨 감소                   |**+**   |볼륨 증가             |

## 개발 SDK

* DirectX11

* FModEx
<br>

## 기술

### 인스턴싱
|<img src="https://postfiles.pstatic.net/MjAyMDA4MDRfOTUg/MDAxNTk2NTMzOTU3OTEz.6Jne7pnmzyeGBUy8lj4HTMJlhXv-mo5zWrGlwHosQicg.vyePXO5c81EoN1mNfWTPeNSt-1Cl0BmFgOEwX24v5WIg.GIF.ashi0/ezgif-6-4d4e77096046.gif?type=w966" width="500" height="350">  |  <img src="https://postfiles.pstatic.net/MjAyMDA4MDRfMjk0/MDAxNTk2NTMzOTU3ODMx.S2pplbVgYGA1Nus1iMLlkUc6HIiqS_xfa3g98wKdFDgg.wKBd5qxgcuI6ktWXKldibhVLf_e2uGY0ne0P7rLhsqwg.GIF.ashi0/ezgif-6-44470591d169.gif?type=w966" width="500" height="350"> |
|:------------------------------------------------:|:-------------------------------------------:|
|**</p> <div align="center"> < particle> </div>**|**</p> <div align="center"> < spectrum > </div>**|
  
파티클과 스펙트럼은 각각 같은 객체를 사용하지만 위치, 크기, 회전량, 색상 정도만 다르기 때문에 <br>
인스턴싱을 사용하여 렌더링에 대한 부하를 줄였습니다.
  
### 안티앨리어싱
|<img src="https://postfiles.pstatic.net/MjAyMDA4MDRfNzcg/MDAxNTk2NTQ4ODc0NzMz.JUvz57BHKL58sQDS1zAfQ3BwBDfPitTDMVcI6wJJ6ugg.qeR85zkOkdTFUqPU2VQyhYg700G5obvmUlrFUuDZlYYg.JPEG.ashi0/SE-5e6d2a1b-3fb2-4510-a771-26bbed930909.jpg?type=w966" width="500" height="350">  |  <img src="https://postfiles.pstatic.net/MjAyMDA4MDRfMTgz/MDAxNTk2NTQ4OTM5MDYw.QVP0J-53NNtTNz4gbaqGLGWY9BL61QLAk9CJDcFKavEg.AAlHKBqXtbIU_GHFeJ1FFmz_3PeihOXAsIJ6I1wGcYMg.JPEG.ashi0/SE-8e137919-3b8c-480e-a71f-a03f9abe16af.jpg?type=w966" width="500" height="350"> |
|:------------------------------------------------:|:-------------------------------------------:|
|**</p> <div align="center"> < before > </div>**|**</p> <div align="center"> < after > </div>**|
  
사각형을 기울여서 렌더링 했을 때 테두리가 계단현상 때문에 부자연스러웠습니다. <br>
관련 내용을 찾아보다가 DirectX에 안티앨리어싱이라는 기술이 있는 것을 보고 <br>
MSAA x8(multi sampling anti-aliasing)을 적용하여 계단현상을 해결했습니다. <br>

### 240 fps 고정
|<img src="https://postfiles.pstatic.net/MjAyMDA4MDRfMTAw/MDAxNTk2NTQ5MTQ5MDc1.PiB5OONB7Qbcila-l3z7EHPbFqE0z7TdYPt5IGb2LqYg.5AoSz-o0kc_HItmQ5gXbdmXjTvzXDpCaIusOF6DdUfYg.JPEG.ashi0/SE-5d4c5c01-305a-4b2d-97a4-879fdbe91343.jpg?type=w966" width="500" height="350">  |  <img src="https://postfiles.pstatic.net/MjAyMDA4MDRfNzgg/MDAxNTk2NTQ5MTc0MzQz.acyIXtIoxoAQyJWaKSwoQtVlf4-sfqBJC-R7JUywBtQg.OgkVkVFGX-Z13BEX2jRArYVyqt-2QB4IP060yj46flUg.JPEG.ashi0/SE-63b1f3ab-5784-44d8-b3f2-20f141295c65.jpg?type=w966" width="500" height="350"> |
|:------------------------------------------------:|:-------------------------------------------:|
|**</p> <div align="center"> < before > </div>**|**</p> <div align="center"> < after > </div>**|

오브젝트 렌더링 간격은 240 fps로 고정했습니다.<br>
GPU 점유율을 낮추기 위해 고사양 모니터 주사율이 240hz인 것을 참고해서 240 fps로 제한했습니다. <br>
