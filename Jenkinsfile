pipeline {
  agent any
  stages {
    stage('Linux') {
      steps {
        sh '''cmake -Bbuild -H.
cmake --build build'''
      }
    }
  }
}