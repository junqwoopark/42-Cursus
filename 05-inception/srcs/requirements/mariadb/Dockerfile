FROM debian:buster

# Dockerfile 작성자
LABEL MAINTAINER="junkpark@student.42seoul.kr"

# image가 올라갔을 때 수행되는 명령어들
# -y 옵션을 넣어서 무조건 설치가 가능하도록 한다.
RUN \
    apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y mariadb-server

EXPOSE 3306

# 컨테이너가 생성 된 이후에 내부의 아파치 서버는 항상 실행중인 상태로 만들어준다.
# apachectl을 foreground(즉, deamon)상태로 돌아가도록 한다.
CMD ["apachectl", "-D", "FOREGROUND"]
