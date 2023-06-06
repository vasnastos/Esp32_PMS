# Setup Grafana in docker

1. Pull Grafana image from docker hub
```
    docker pull grafana/grafana
```

2. Create a container exporting port 3000
```
    docker run -d -p 3000:3000 --name=weatherApp grafana/grafana
```

3. Create an account to grafana
[https://grafana.com/](https://grafana.com/)

4. Login to Grafana

**User: admin**
**Password:weatherAppIOT**

5. 