R"rawText(
<html>
  <head>
    <title>MPU9250 web visualisation</title>
    <style>
      canvas {
        width: 100%;
        height: 100%;
      }
    </style>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/three.js/101/three.min.js"></script>
    <script>
      var scene;
      var camera;
      var renderer;

      var cube;

      function render() {
        requestAnimationFrame(render);
        renderer.render(scene, camera);
      }

      function CubeBegin() {
        scene = new THREE.Scene();
        camera = new THREE.PerspectiveCamera(
          75,
          window.innerWidth / window.innerHeight,
          0.1,
          1000
        );
        renderer = new THREE.WebGLRenderer();

        renderer.setSize(window.innerWidth, window.innerHeight);
        document.body.appendChild(renderer.domElement);
        var geometry = new THREE.BoxGeometry(100, 100, 100);
        var cubeMaterials = [
          new THREE.MeshBasicMaterial({ color: 0xfe4365 }),
          new THREE.MeshBasicMaterial({ color: 0xfc9d9a }),
          new THREE.MeshBasicMaterial({ color: 0xf9cdad }),
          new THREE.MeshBasicMaterial({ color: 0xc8cba9 }),
          new THREE.MeshBasicMaterial({ color: 0x83af98 }),
          new THREE.MeshBasicMaterial({ color: 0xe5fcc2 })
        ];

        var material = new THREE.MeshFaceMaterial(cubeMaterials);
        cube = new THREE.Mesh(geometry, material);
        scene.add(cube);

        camera.position.z = 200;

        render();
      }
      function WebSocketBegin() {
        CubeBegin();

        if ("WebSocket" in window) {
          // Let us open a web socket
          ws = new WebSocket(
            location.hostname.match(/\.husarnetusers\.com$/)
              ? "wss://" + location.hostname + "/__port_8001/"
              : "ws://" + location.hostname + ":8001/"
          );
          // ws = new WebSocket(
          //   "wss://fc94f91f5992989f83474cc8abf7329b-8001.husarnetusers.com"
          // );

          ws.onopen = function() {
            // Web Socket is connected
          };

          ws.onmessage = function(evt) {
            //create a JSON object
            var jsonObject = JSON.parse(evt.data);
            var q0 = jsonObject.q0;
            var q1 = jsonObject.q1;
            var q2 = jsonObject.q2;
            var q3 = jsonObject.q3;

            var quat1 = new THREE.Quaternion(q1, q2, q3, q0);
            var quat2 = new THREE.Quaternion(1, 0, 0, 0);

            cube.quaternion.multiplyQuaternions(quat1, quat2);
          };

          ws.onclose = function() {
            // websocket is closed.
            alert("Connection is closed...");
          };
        } else {
          // The browser doesn't support WebSocket
          alert("WebSocket NOT supported by your Browser!");
        }
      }
    </script>
  </head>

  <body onLoad="javascript:WebSocketBegin()">
  </body>
</html>

)rawText"