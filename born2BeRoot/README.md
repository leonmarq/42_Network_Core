*This project has been created as part of the 42 curriculum by leonmarq*

# Description
a custom debian installation based on the requirements of the born2beroot subject v5.0 (https://cdn.intra.42.fr/pdf/pdf/190089/en.subject.pdf)

## Choice of operating system

### Debian

| Pros | Cons |
| --- | --- |
| Large community and extensive documentation | Package versions can be older than in some other distributions |
| Very stable and widely used in learning environments | Not as enterprise-focused out of the box as Rocky Linux |
| Easy package management with `apt` and broad repository support | Some enterprise tooling is more commonly documented for RHEL-like systems |

### Rocky Linux

| Pros | Cons |
| --- | --- |
| Enterprise-oriented and RHEL-compatible ecosystem | Smaller beginner community compared to Debian |
| Strong fit for production-like server environments | Can be less beginner-friendly for first Linux administration projects |
| Long-term stability expectations for enterprise workflows | Some tutorials and learning resources are less abundant for newcomers |

### Conclusion

i chose debian, because it is the more common and easiest to set up than Rocky Linux

## Security
### Linux Security Modules (LSMs)
AppArmor is more commonly used and easier to set up than SELinux. but later allows for more fine grained policies.
Therefore AppArmor gets used in low-risk enviroments and SELinux for Enterprise-grade security.
AppArmor is installed by default on Ubuntu.

### Firewall
Both UFW (Uncomplicated Firewall) and firewalld are user-friendly management tools (frontends) for underlying Linux packet filtering frameworks (iptables or nftables). UFW is the standard on Debian/Ubuntu systems, while firewalld is standard on Red Hat-based distributions (like RHEL, Fedora, and CentOS).

## Options of VMs
VirtualBox is the industry standard for Intel-based x86 machines, while UTM is built specifically for macOS (utilizing Apple's hypervisor framework) to run ARM-based virtual machines flawlessly

# Instructions
## Entry
clone the VM to not change the original. then boot the clone  and unlock the encrypted disk.
Sign in with your credentials via ssh for ease of use on port 4242 via localhost:
`ssh <name>@localhost -p 4242`

## Special Features
1. password protected root folder
2. strict password policy enforced with libpam-pwquality and defined in: `/etc/pam.d/common-password`
3. a script which runs every 10 minutes and broadcasts system information, which you can manage by: `sudo crontab -e`
4. lighttpd providing a wordpress running on port 80 internally, but forwards usually to 8080. Therefore find it here: `http://localhost:8080/`
5. Openlightspeed(http://localhost:8088/) hosting a static website(http://localhost:8088/)

## Useful Commands
- verify no grafical interface is installed:
  - `ls /usr/bin/*session` outputs `/usr/bin/dbus-run-session`
- check firewall: `sudo ufw status` and `sudo service ufw status`
- check ssh: `sudo service ssh status`
- operating system: `uname --kernel-version`
- list users of group, here sudo: `getent group sudo`
- modify the hostname here:
  1. `sudo nano /etc/hostname`
  2. `sudo nano /etc/hosts`
- check for installed program, here sudo: `which sudo`

## Important files
- sudo configuration: `/etc/sudoers.d/sudo_config`
- Password policy: `/etc/pam.d/common-password` and `/etc/login.defs`
- broadcast script: `/home/leonmarq/display_info.sh`

# Resouces
https://wiki.debian.org/
https://www.geeksforgeeks.org/
https://noreply.gitbook.io/
https://tuxcare.com/blog/selinux-vs-apparmor/
