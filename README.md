# CompactRoutingBasedMappingSystem-

Thesis Title:
Experimental Implementation of a Compact Routing based Mapping System for the Locator/ID Separation Protocol (LISP).

Abstract:
It is by now something of a cliché to talk about the "explosive" or "exponential" growth of the Internet. However, the fact remains; the number of participant networks in the Internet has grown phenomenally, far beyond what the initial designers had in mind. This unprecedented growth has caused the existing Internet routing architecture to face serious scalability issues. Single numbering space, multi-homing, and trace engineering, are making routing tables (RTs) of the default free zone (DFZ) to grow very rapidly. In order to solve this issue, it had been proposed to review the Internet addressing architecture by separating the end-systems identifiers' space and the routing locators' space. Several such proposals exist, among which Locator/Identifier Separation Protocol (LISP) is the only one already being shipped in production routers. As LISP considers two different address spaces, a mapping system is required to provide bindings between the two. Out of several proposed mapping systems, LISP-ALT has emerged as the de-facto one, as it has a complete implementation for the Cisco NX-OS and IOS platforms. LISP-ALT's downsides being, its wide reuse of BGP and assuming a "highly aggregatable" or administratively 
pre-allocated IP address space; making it unsuitable for solving the routing  scalability problem.

The concept of Compact Routing on the other hand, guarantees that the size of the RT will grow sub-linearly, which goes a long way in solving the scalability problem of DFZ RTs. It also puts an upper bound to the latency experienced by a datagram packet. The major drawback here is that, the "label"/address in Compact Routing comprises of three parts which cannot be implemented by any existing addressing scheme. Furthermore, it assumes a static network topology, which is absurd in the current Internet infrastructure.
 
Therefore, this thesis presents the implementation of an experimental mapping system called CRM that combines the perceived benefits of both Compact Routing and LISP. In this mapping system, the critical functions that affect the scalability of the routing system are grounded to the theory of Compact Routing; so that we might over come the shortcomings of LISP-ALT. We mitigated Compact Routing's presumption of a static network by reusing LISP's registration messages and choosing landmarks dynamically based on their capability to aggregate. The key objective of this thesis work is to provide proof of concept, to give us first-hand experience regarding the complicacies that arise with the actual development of such a mapping system.

Our work also includes a comprehensive comparison between CRM and LISP-ALT. The results suggest that, CRM would be feasible in the current Internet if deployed and it would be far less expensive than LISP-ALT.

Keywords:          LISP-ALT, Compact Routing, BGP, scalability, Aggregation
Language:          English

Implementation Code of CRM

The experimental prototype described in this thesis is implemented using C(GCC). This appendix presents C ode that implements some main sub-tasks of CRM. However, the
reader must realize that, the actual prototype is comprised of many more complicated functions that are not shown here for the sake of simplicity. This appendix is intended to
provide the reader a "high-level" view.


