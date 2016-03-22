#!/bin/bash

GITHUB_URL=$(git remote -v | grep push | awk '{print $2}')
PROJECT_NAME=$(echo $GITHUB_URL | awk -F/ '{print $NF}' | cut -d. -f1)
PROJECT_DIR=/tmp/$PROJECT_NAME
RENDU_URL=$1

echo NAME: $PROJECT_NAME
echo DIR: $PROJECT_DIR

if [ -n "$RENDU_URL" ]; then
	git clone $42_URL /tmp
else
	if [ -d "$PROJECT_DIR" ]; then
		rm -rf $PROJECT_DIR
	fi
	mkdir $PROJECT_DIR
fi

CPY=(src includes Makefile)

for DIR in ${CPY[@]}; do
	cp -r $DIR $PROJECT_DIR
done

make -C $PROJECT_DIR re
#find $PROJECT_DIR -mindepth 2 -type d -name ".git" -exec rm -rf {} \;
