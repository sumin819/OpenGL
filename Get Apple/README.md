## Instrctions

1.	화면에는 사람과 테이블, 테이블 위에 있는 사과가 있습니다.

2. 사람은 중심 물체인 몸통과 몸통에 붙어있는 머리, 팔 두개, 다리 두개로 이루어집니다.

&emsp;&emsp;&emsp;A. 다리는 몸통으로부터 허벅지-종아리-발까지 이어지는 다관절 형태입니다.

&emsp;&emsp;&emsp;B. DrawArm(int n)에서 n의 값을 1과 2를 주어 각각 한쪽 팔을 다른 각도로 움직이게 설정합니다.

&emsp;&emsp;&emsp;C. DrawLeg(), DrawCalf(), DrawFoot()은 다리를 그리게 합니다. 

&emsp;&emsp;&emsp;D. B와 C의 함수를 사용해 사람을 그립니다. 

3. 테이블은 네모난 판을 중심으로 다리 4개가 붙어있으며 테이블 위에는 사과가 놓여있습니다. 

&emsp;&emsp;&emsp;A. class vec3과 vector<Apple> apples를 사용해 테이블 위 사과의 좌표를 저장했습니다. 

&emsp;&emsp;&emsp;B. 저장한 좌표를 사용해 사용자가 테이블 4면 근처에 가면 사과를 얻게 되고 화면에서 사과는 사라집니다. 

&emsp;&emsp;&emsp;&emsp;(EatCheck()와 bool eat을 사용) 

4. 3개의 타이머 콜백이 사용됩니다.

&emsp;&emsp;&emsp;A. MyTimerLL, MyTimerLR은 각각 다리 하나를 움직이게 하며 걷는 모양을 만들기 위해 MyTimerLR은 MyTimerLL에 비해 1초 늦게 시작됩니다.

&emsp;&emsp;&emsp;B. MyTimerA은 양 팔을 움직이게 합니다. 

5. 마우스를 조작해 시점을 변환할 수 있습니다. 

6. 사람은 키보드 조작과 연관되어 있습니다.

&emsp;&emsp;&emsp;A. 좌, 우, 아래, 위 버튼을 누르면 사람이 움직입니다.

&emsp;&emsp;&emsp;B. a버튼을 누르면 시계방향으로, s버튼을 누르면 반시계 방향으로 사람이 회전합니다.

7. 조명 기능을 사용하였고 사과, 사람, 테이블, 바닥에 각각 다른 재질을 부여했습니다. 
