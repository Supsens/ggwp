/*
=========================================================
🧠 NETWORK COMMANDS – THEORY NOTES
=========================================================

1️⃣ ping [domain name]
   • Purpose: Tests connectivity between your PC and a remote host.
   • How it works: Sends ICMP Echo Request packets and waits for Echo Replies.
   • Shows: Round-trip time, packet loss, TTL (Time To Live).
   • Used for: Checking if a host or website is reachable.

---------------------------------------------------------

2️⃣ ipconfig   (Windows) / ifconfig (Linux)
   • Purpose: Displays IP address, subnet mask, and default gateway.
   • ipconfig /all → Shows detailed adapter, DNS, and MAC info.
   • ipconfig /release /renew → Refreshes IP from DHCP.
   • Used for: Diagnosing local network adapter or IP issues.

---------------------------------------------------------

3️⃣ tracert [domain name]   (traceroute in Linux)
   • Purpose: Traces the route packets take to reach a destination.
   • How it works: Sends packets with increasing TTL; each router returns ICMP Time Exceeded.
   • Shows: All intermediate hops (routers) with delay times.
   • Used for: Finding where a network connection slows or fails.

---------------------------------------------------------

4️⃣ nslookup [domain name]
   • Purpose: Queries DNS servers to resolve domain names into IP addresses.
   • Can also show MX, TXT, and other DNS record types.
   • Used for: Testing DNS configuration or resolving issues.

---------------------------------------------------------

5️⃣ netstat -an
   • Purpose: Displays all active network connections and listening ports.
   • “-a” → shows all connections, “-n” → shows numeric addresses.
   • Shows: Local and foreign addresses, port numbers, and connection states.
   • Used for: Monitoring open ports and detecting suspicious connections.

---------------------------------------------------------

6️⃣ arp -a
   • Purpose: Displays the ARP (Address Resolution Protocol) cache table.
   • Shows: Mapping between IP addresses and their MAC addresses.
   • Used for: Checking if local devices are properly resolved at the data-link layer.

---------------------------------------------------------

7️⃣ hostname
   • Purpose: Displays the computer’s host name (network name).
   • Used for: Identifying the local system on a network.

---------------------------------------------------------

8️⃣ getmac
   • Purpose: Displays the MAC address (physical address) of your network interfaces.
   • Used for: Device identification or troubleshooting hardware address conflicts.

---------------------------------------------------------

9️⃣ route print
   • Purpose: Displays the IP routing table.
   • Shows: Destination networks, gateways, interface metrics, and routes.
   • Used for: Diagnosing routing problems and verifying network paths.

---------------------------------------------------------

10️⃣ pathping [domain name]
    • Purpose: Combines ping + tracert.
    • How it works: Traces the route and calculates packet loss and latency for each hop.
    • Used for: Detailed route analysis and identifying network congestion points.

---------------------------------------------------------

11️⃣ Get-DnsClientCache   (PowerShell command)
    • Purpose: Displays the contents of the local DNS resolver cache.
    • Shows: Recently resolved domain names with their IP addresses.
    • Used for: Checking cached DNS entries or clearing DNS cache when needed.

---------------------------------------------------------

12️⃣ dig [domain name]   (Linux / macOS)
    • Purpose: “Domain Information Groper” — advanced DNS lookup tool.
    • Shows: Detailed DNS records like A, MX, NS, and SOA.
    • Used for: Advanced DNS troubleshooting and analysis.

=========================================================
📘 Summary:
These commands are essential for diagnosing and troubleshooting network connectivity,
IP configuration, DNS resolution, and routing issues.
=========================================================
*/
