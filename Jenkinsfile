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
        sh 'dnf install -y cmake qt5-qtquickcontrols2-devel gcc-c++ ninja-build'
        sh 'cmake -Bbuild -H. -GNinja'
        sh 'cmake --build build'
      }
    }
  }
  environment {
    CLICOLOR_FORCE = '1'
  }
}
