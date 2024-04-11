#! /bin/bash

#https://pimylifeup.com/phpmyadmin-docker/?fbclid=IwAR3TcKIte-glonyZ9Az5DRmfc144uuEIWEHe3eXOrLZ4u0lcsQgnWaOFHWM_aem_Abya_gHBge_4_uP5EbicRMqFwFb-cqH-NWhiZeP6M4q_w3Nf5TtCfPKQS4XimKhzQy3-94e2NxHLjUWtAZkFxjoq

curl -sSL https://get.docker.com | sh
sudo usermod -aG docker $USER
sudo reboot
sudo mkdir -p /opt/stacks/phpmyadmin
cd /opt/stacks/phpmyadmin
sudo nano compose.yaml
version: '3'

services:
  phpmyadmin:
    image: phpmyadmin
    container_name: pma
    ports:
      - 8080:80
    environment:
      - PMA_ARBITRARY=1 
	  

version: '3'

services:
  db:
    image: mariadb:latest
    environment:
      MYSQL_ROOT_PASSWORD: examplerootpass
      MYSQL_DATABASE: exampledb
      MYSQL_USER: exampleuser
      MYSQL_PASSWORD: examplepass
    volumes:
      - ./data:/var/lib/mysql
    ports:
      - "3306:3306"
  phpmyadmin:
    image: phpmyadmin/phpmyadmin
    container_name: pma
    ports:
      - 8080:80
    environment:
      - PMA_HOST="db"
      - PMA_ARBITRARY=1 
	  

docker compose up -d

hostname -I

http://<IPADDRESS>:8080



Updating your phpMyAdmin Docker Container

cd /opt/stacks/phpmyadmin
docker compose pull
docker compose up -d
