PINGFANG_MAG_CONFIG=$(catkin_find --etc --first-only pingfang_base mag_config.yaml 2>/dev/null)
if [ -z "$PINGFANG_MAG_CONFIG" ]; then
  PINGFANG_MAG_CONFIG=$(catkin_find --share --first-only pingfang_base config/mag_config_default.yaml 2>/dev/null)
fi

export PINGFANG_MAG_CONFIG
