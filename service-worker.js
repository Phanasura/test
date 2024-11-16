// service-worker.js
self.addEventListener('install', (event) => {
    console.log('Service Worker installing...');
    event.waitUntil(
      caches.open('static-cache').then((cache) => {
        return cache.addAll([
          '/',                // Tệp HTML chính
          '/index.html',      // Đường dẫn đến tệp HTML
          '/minicon.png',// Biểu tượng 192px
          '/maxicon.jpg' // Biểu tượng 512px
        ]);
      })
    );
  });
  
  self.addEventListener('fetch', (event) => {
    console.log('Fetching:', event.request.url);
    event.respondWith(
      caches.match(event.request).then((response) => {
        return response || fetch(event.request);
      })
    );
  });
  