pipeline {
  agent {
    docker {
      image 'fedora:30'
      args '-u root'
    }
  }
  stages {
    stage('Linux') {
      steps {
        sh 'dnf install -y cmake qt5-qtquickcontrols2-devel gcc-c++ ninja-build boost-devel'
        sh 'cmake -B/tmp/build -H. -GNinja'
        sh 'cmake --build /tmp/build'
      }
    }
  }
  environment {
    CLICOLOR_FORCE = '1'
  }
}
