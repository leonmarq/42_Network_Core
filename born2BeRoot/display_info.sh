#!/bin/bash
PATH=/usr/sbin:/usr/bin:/sbin:/bin

arch=$(uname -a)

cpu_f=$(grep "physical id" /proc/cpuinfo | wc -l)
cpu_v=$(grep processor /proc/cpuinfo | wc -l)

ram_total=$(free --mega | awk '$1 == "Mem:" {print $2}')
ram_use=$(free --mega | awk '$1 == "Mem:" {print $3}')
ram_percent=$(free --mega | awk '$1 == "Mem:" {printf("(%.2f%%)\n", $3/$2*100)}')

disk_total=$(df -m | grep "/dev/" | grep -v "/boot" | awk '{disk_t += $2} END {printf ("%.1fGb\n"), disk_t/1024}')
disk_use=$(df -m | grep "/dev/" | grep -v "/boot" | awk '{disk_u += $3} END {print disk_u}')
disk_percent=$(df -m | grep "/dev/" | grep -v "/boot" | awk '{use += $3} {total += $2} END {printf("(%d%%)\n"), use/total*100}')

cpu_l=$(vmstat 1 2 | tail -1 | awk '{printf $15}')
cpu_op=$(expr 100 - $cpu_l)
cpu_fin=$(printf "%.1f" $cpu_op)

time_lb=$(date -d "$(uptime -s)" "+%Y-%m-%d %H:%M")
lvm_u=$(if [ $(lsblk | grep "lvm" | wc -l) -gt 0 ]; then echo yes; else echo no; fi)
tcp=$(ss -ta | grep ESTAB | wc -l)

log_u=$(users | wc -w)

ip=$(hostname -I | cut -d ' ' -f1)
mac=$(ip link | grep "link/ether" | awk '{print $2}')

cmd=$(journalctl _COMM=sudo | grep COMMAND | wc -l)

# Create the system info message
message="
	Architecture: $arch
	CPU physical: $cpu_f
	vCPU: $cpu_v
	Memory Usage: $ram_use/${ram_total}MB $ram_percent
	Disk Usage: $disk_use/${disk_total} $disk_percent
	CPU load: $cpu_fin%
	Last boot: $time_lb
	LVM use: $lvm_u
	Connections TCP: $tcp ESTABLISHED
	User log: $log_u
	Network: IP $ip ($mac)
	Sudo: $cmd cmd
"

# Create broadcast header like wall
timestamp=$(date '+%a %b %d %H:%M:%S %Y')
current_tty=$(tty 2>/dev/null || echo "console")
current_user=$(whoami)
broadcast_header="Broadcast message from $current_user@$(hostname) ($current_tty) ($timestamp):"

full_message="$broadcast_header
$message"

# Try wall first
printf '%s' "$message" | /usr/bin/wall 2>/dev/null

# Also write directly to all pts devices with broadcast header
for tty in /dev/pts/[0-9]*; do
	[ -e "$tty" ] || continue
	printf '\r\n%s\r\n' "$full_message" > "$tty" 2>/dev/null
done
