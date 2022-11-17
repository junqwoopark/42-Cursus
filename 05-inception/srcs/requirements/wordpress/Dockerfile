FROM debian:buster

# Dockerfile 작성자
LABEL MAINTAINER="junkpark@student.42seoul.kr"

# image가 올라갔을 때 수행되는 명령어들
# -y 옵션을 넣어서 무조건 설치가 가능하도록 한다.
RUN \
    apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y wordpress \
    apt-get install -y php-fpm


# nginx가 기본적으로 80포트를 사용하기 때문에 expose를 이용해 nginx server로 접근이 가능하도록 한다.
EXPOSE 9000 3306

# 컨테이너가 생성 된 이후에 내부의 nginx 서버는 항상 실행중인 상태로 만들어준다.
# nginx를 foreground(즉, deamon)상태로 돌아가도록 한다.
# CMD ["nginx", "-g", "daemon off;"]
