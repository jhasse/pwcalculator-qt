pipeline {
  agent {
    docker { image 'fedora:30' }
  }
  stages {
    stage('Linux') {
      steps {
        sh 'dnf install -y cmake qt5-qtquickcontrols2-devel
        sh 'cmake -Bbuild -H.'
        sh 'cmake --build build'
      }
    }
  }
  environment {
    CLICOLOR_FORCE = '1'
  }
}
