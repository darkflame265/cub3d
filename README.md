# cub3D

현재 문제점.
1. 맵 피싱에서 맨파일 맨 마지막 줄을 지우면, 에러가 뜸. (단 맵 정보줄 맨 아래에서 한 칸 위에 '0'이 존재할 시.)
2. 해상도가 크면 --save 기능에서 segment Error가 뜸.
  (해상도가 1500, 1500일땐 문제 없이 --save가 되는데, 2000 2000이면 안 됨.) (처음엔 모니터 해상도 문제인 줄 알았으나 그것도 아님.)
3. 마지막으로 스프라이트 원리나 쪼오금 공부해보자.


P.s 현재 한 거, Velog블로그에 정리해보자.
1. mlx_get_screen_size() 함수가 작동이 안 돼요.
 내 경우엔 mlx파일을 minilbx_opengl_201901021 즉, opengl을 사용했다. (opengl은 정적, mms는 동적이라는데 잘 몰라.)
 그런데 이대로 쓰면, 다른 mlx함수는 잘 되는데, mlx_get_screen_size함수는 작동이 안된다.
 (헤더파일에 저 함수가 존재하지도 않음.)
 해결법:
 https://gitlab.com/OctopusET/minilibx_opengl_custom/(여기서 mlx_get_screen.m)파일을 가져와 opengl 폴더에 넣는다.
 그리고 opengl의 헤더파일, 즉 mlx.h 파일에도 mlx_get_screen_size 선언해야 함.

2. 노미네이터에 가변 길이 배열 사용 불가능이라고 적혀있다.
 가변길이배열: 배열을 지정할 때, 배열의 크기를 변수로 넣어 지정할 수 없다.
 int a = 3;
 char c[a]; <- 이런 거 안 됨.
 내 경우엔 비트맵 이미지 만드는(--save) 기능 만들 때, 실수로 써버렸다.
 
 unsigned char	image[info->gnl_info.hei][info->gnl_info.wid][BP];
 위 선언에서 배열안에, hei, wid, 즉 변수가 들어가 있어서 안됨. BP는 define으로 만든거라 괜찮.
 

P.s 블랙홀 데이 3일이었는데, 순식간에 64일 됐다. 개꿀ㅎㅎ.
