#mostly stolen from rmkit

APP=${1}
BASE_DIR="/home/root"
RM_USER="root"

function kill_remote_app() {
  ssh ${RM_USER}@${REMARKABLE_HOST} killall ${APP} 2> /dev/null
}

function cleanup() {
  kill_remote_app
  ssh ${RM_USER}@${REMARKABLE_HOST} systemctl restart xochitl
  echo "FINISHED"
  exit 0
}

trap cleanup EXIT
trap cleanup SIGINT

scp cmake-build-docker/${APP} ${RM_USER}@${REMARKABLE_HOST}:${BASE_DIR}/${APP}
kill_remote_app
echo "RUNNING ${APP}"
#remove rm2fb-client if you're running on a RM1
ssh ${RM_USER}@${REMARKABLE_HOST} /opt/bin/rm2fb-client ${BASE_DIR}/${APP}
