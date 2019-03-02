#!/bin/bash

YEAR=`date +%Y`
MONTH=`date +%m`
DAY=`date +%d`

FILENAME='master_scoreboard.xml'
FILEPATH="http://gd2.mlb.com/components/game/mlb/year_$YEAR/month_$MONTH/day_$DAY/$FILENAME"
NEW_NAME=../data/`date +%Y_%m_%d_%H_%M_%S_`$FILENAME 

curl $FILEPATH > $NEW_NAME
