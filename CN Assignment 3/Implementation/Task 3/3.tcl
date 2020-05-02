#Create a simulator object
set ns [new Simulator]

#Define different colors for data flows 
$ns color 1 Blue

#Open the NAM trace file
set nf [open out.nam w]
$ns namtrace-all $nf
set tf [open out.tr w] 						
$ns trace-all $tf

proc finish { } {     
	global ns nf tf
	# clears trace file contents 
	$ns flush-trace  
	#Close the NAM trace file   								
	close $nf
	#Execute NAM on the trace file
	close $tf
	exec nam out.nam &
	exit 0
}

#Create four nodes
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

# establishing links
$ns duplex-link $n1 $n2 10Mb 10ms DropTail
$ns duplex-link $n2 $n3 0.8Mb 100ms DropTail
$ns queue-limit $n1 $n2 2
$ns queue-limit $n2 $n3 2

#Give node position (for NAM)
$ns duplex-link-op $n1 $n2 orient right
$ns duplex-link-op $n2 $n3 orient right

#Monitor the queue for link (n2-n3). (for NAM)
$ns duplex-link-op $n2 $n3 queuePos 0.5

#attaching transport layer protocols
set udp0 [new Agent/UDP] 						
$ns attach-agent $n1 $udp0
set null0 [new Agent/Null] 						
$ns attach-agent $n3 $null0
$ns connect $udp0 $null0
$udp0 set fid_ 1

#attaching application layer protocols
#Setup a CBR over UDP connection
set cbr0 [new Application/Traffic/CBR] 	
$cbr0 set packetSize 1000 
$cbr0 set interval 0.005
$cbr0 attach-agent $udp0

$ns at 0.1 "$cbr0 start"
$ns at 2.5 "finish"

#Print CBR packet size and interval
puts "CBR packet size = [$cbr0 set packetSize]"
puts "CBR interval = [$cbr0 set interval]"

$ns run
