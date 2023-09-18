#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
CYAN='\033[0;36m'
BOLD='\033[1m'
NC='\033[0m'

echo -en "Welcome to launch_batch.sh by ${BOLD}tmatis${NC}!\n\n"

echo -en "What size of board do you want to test? "
read size

if ! [[ "$size" =~ ^[0-9]+$ ]]; then
    echo -e "${RED}Error: ${BOLD}$size${NC} is not a positive integer!${NC}"
    exit 1
fi

echo -en "How many team do you want to test? "
read team_count

if ! [[ "$team_count" =~ ^[0-9]+$ ]]; then
    echo -e "${RED}Error: ${BOLD}$team_count${NC} is not a positive integer!${NC}"
    exit 1
fi

echo -en "How many player per team do you want to test? "
read player_count

if ! [[ "$player_count" =~ ^[0-9]+$ ]]; then
    echo -e "${RED}Error: ${BOLD}$player_count${NC} is not a positive integer!${NC}"
    exit 1
fi

echo -en "What speed do you want to test? "
read speed

if ! [[ "$speed" =~ ^[0-9]+$ ]]; then
    echo -e "${RED}Error: ${BOLD}$speed${NC} is not a positive integer!${NC}"
    exit 1
fi

# print a resume of test parameters
echo -e "\n${CYAN}Test parameters:${NC}"
echo -e "  ${BOLD}Board size:${NC} $size"
echo -e "  ${BOLD}Team count:${NC} $team_count"
echo -e "  ${BOLD}Player count:${NC} $player_count"
echo -e "  ${BOLD}Speed:${NC} $speed\n"

# ask for confirmation
echo -en "${CYAN}Do you want to continue? [y/n] ${NC}"
read confirm

if [ "$confirm" != "y" ]; then
    echo -e "${RED}Aborting...${NC}"
    exit 1
fi

# player count = team count * player count
total_players=$(($team_count * $player_count))

# launch the first instance that create the board
./lemipc $size 1 $total_players $speed &> /dev/null &

# launch the visualizer

./lemipc_visualizer $size &> /dev/null &
PID_VISUALIZER=$!

# launch all ther other teams
for (( i=1; i<=$player_count; i++ ))
do
    for (( j=1; j<=$team_count; j++ ))
    do
        # if j == 1 and i == 1, it's the first instance that create the board
        if [ $j -eq 1 ] && [ $i -eq 1 ]; then
            continue
        fi
        ./lemipc $size $j $i $speed &> /dev/null &
    done
done

wait $PID_VISUALIZER
