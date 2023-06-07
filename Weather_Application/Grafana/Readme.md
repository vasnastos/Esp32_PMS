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
5. Grafana Access Token(All permissions)

   ```
   j4gAjJJw_s4at4TppMPZeREhVNri7qwgvafdHt-c545GBHPZ_QOa9veFiNhc4941FjKdfE_GaTufZaB2pJrsqA==
   ```
6. Flux query for temperature(Previous day records)

   ```
   from(bucket: "Weather")
     |> range(start: -1d)
     |> filter(fn: (r) => r._field=="Temperature")
     |> yield(name: "_results")


   ```
7. Flux query for humidity(Previous day records)

   ```
   from(bucket: "Weather")
     |> range(start: -1d)
     |> filter(fn: (r) => r._field=="Humidity")
     |> yield(name: "_results")
   ```
