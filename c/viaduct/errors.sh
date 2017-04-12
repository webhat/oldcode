
#!/bin/bash

ECHO="echo -e"
NAUGHTY="strcpy malloc atoi"
CODE=`find . -name "*.[chi]*"`

if [ "$USER" = "redhat" ]; then
		$ECHO "Glad to see you my creator!"
fi

$ECHO "This program check for naughty code"

for BAD in $NAUGHTY; do
	$ECHO "Checking: ${BAD}"
	echo $@ | xargs grep -n ${BAD}
done
